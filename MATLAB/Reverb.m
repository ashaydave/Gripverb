classdef Reverb < audioPlugin
    properties % tunable parameters with default values
        feedback = 0.8 % comb filter parameter -> ROOM SIZE PARAMETER
        damping = 0.2 % comb filter parameter
        mix = 50
        stereoSeperation = 50
        masterGain = 5 
    end

    properties (Access = private)
        combFilterBank % bank of 8 comb filters
        allPassBank % cascade of 4 allpass filters
    end
    
    properties (Constant)
        combFilterDelay = [1557 1617 1491 1422 1277 1356 1188 1116]
        allPassDelay = [225 556 441 341]
        offset = 23 % stereo seperation between right and left channel
        numberCombFilters = 8
        numberAPFilters = 4
        allPassGain = 0.5 % fixed allpass filter parameter
    end

    properties (Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('feedback', 'Mapping',{'lin',0.1, 0.98}, 'Style', 'rotaryknob', 'Layout', [3,1], 'DisplayName', 'Room Size', 'DisplayNameLocation', 'Above'),...
            audioPluginParameter('damping',  'Mapping',{'lin',0.1, 1}, 'Style', 'rotaryknob', 'Layout', [3,2], 'DisplayName', 'Damping', 'DisplayNameLocation', 'Above'), ...
            audioPluginParameter('stereoSeperation', 'Mapping',{'lin',0, 100}, 'Style', 'rotaryknob', 'Layout', [3,3], 'DisplayName', 'Width', 'DisplayNameLocation', 'Above'), ...
            audioPluginParameter('mix', 'Label', '%', 'Mapping',{'lin',0, 100}, 'Style', 'rotaryknob', 'Layout', [3,4], 'DisplayName', 'Mix', 'DisplayNameLocation', 'Above'), ...
            audioPluginParameter('masterGain', 'Label', 'dB', 'Mapping',{'lin', -12, 12}, 'Style', 'rotaryknob', 'Layout', [3,5], 'DisplayName', 'Gain', 'DisplayNameLocation', 'Above'), ...
            audioPluginGridLayout('RowHeight', [20, 20, 160, 120, 160], 'ColumnWidth', [100, 100, 100, 100, 100]));
    end
    
    methods
        
        function obj = Reverb 

            % Set up comb filters
            obj.combFilterBank = cell(obj.numberCombFilters,2);
            for n = 1:obj.numberCombFilters
                obj.combFilterBank{n,1} = lowPassCombFilter(obj.combFilterDelay(n),obj.damping, obj.feedback);
                obj.combFilterBank{n,2} = lowPassCombFilter(obj.combFilterDelay(n) + obj.offset, obj.damping, obj.feedback);
            end

            % set up allpass filters
            obj.allPassBank = cell(obj.numberAPFilters,2);
            for n = 1:obj.numberAPFilters 
                obj.allPassBank{n,1} = allPassFilter(obj.allPassDelay(n), obj.allPassGain);
                obj.allPassBank{n,2} = allPassFilter(obj.allPassDelay(n) + obj.offset, obj.allPassGain);
            end
        end
        
        function update(obj)
            % update comb filter parameters
            for n = 1:obj.numberCombFilters
                for k = 1:2
                    obj.combFilterBank{n,k}.damping = obj.damping;
                    obj.combFilterBank{n,k}.feedback = obj.feedback;
                end
            end
        end
        
        function out = process(obj, x)
            out = zeros(size(x));
            for n = 1:obj.numberCombFilters % parallel comb filters
                out(:,1) = out(:,1) + process(obj.combFilterBank{n,1}, x(:,1))/obj.numberCombFilters;
                out(:,2) = out(:,2) + process(obj.combFilterBank{n,2}, x(:,2))/obj.numberCombFilters;
            end
            for n = 1:obj.numberAPFilters % cascaded all-pass filters
                out(:,1) = process(obj.allPassBank{n,1}, out(:,1));
                out(:,2) = process(obj.allPassBank{n,2}, out(:,2));
            end
            reverbMix = obj.mix/100;
            stereoSep = obj.stereoSeperation/100;
            gain = obj.masterGain/20;
            outMix = (ones(2)+stereoSep*[1 -1; -1 1])/2;
            out = gain*(reverbMix*out*outMix+(1-reverbMix)*x);
        end
    end
    
end

