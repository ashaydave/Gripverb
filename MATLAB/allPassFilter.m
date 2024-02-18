classdef allPassFilter

    properties
        delay
        gain
    end
    properties (Access = private)
        xbuffer
        ybuffer
        head
    end
    
    methods
        function obj = allPassFilter(delay, gain) % constructor
            obj.delay = delay;
            obj.gain = gain;
            obj.xbuffer = zeros(1,delay);
            obj.ybuffer = zeros(1,delay);
            obj.head = 0;
        end
        
        function y = process(obj, x)
            N = length(x);
            y = zeros(N,1);
            
            g = obj.gain;
            del = obj.delay;
            p = obj.head;
            for n=1:N
                y(n) = g*obj.ybuffer(p+1) - x(n) + (1+g)*obj.xbuffer(p+1);
                obj.ybuffer(p+1) = y(n);
                obj.xbuffer(p+1) = x(n);
                p = mod(p+1,del);
            end
            obj.head = p;
        end
    end
    
end

