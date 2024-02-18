classdef lowPassCombFilter
    
    properties
        delay
        damping
        feedback
    end
    
    properties (Access=private)
        buffer % delay line
        head % delay line pointer
        state % filter state variable
    end
    
    methods
        function obj = lowPassCombFilter(delay, damping, feedback) % constructor
            obj.delay = delay;
            obj.damping = damping;
            obj.feedback = feedback;
            obj.buffer = zeros(delay,1);
            obj.head = 0;
            obj.state = 0;
        end
        
        function y = process(obj, x)
            N = length(x);
            y = zeros(N,1);
            
            d = obj.damping;
            f = obj.feedback;
            del = obj.delay;
            s = obj.state;
            p = obj.head;
            for n=1:N
                y(n) = d*s + f*(1-d)*obj.buffer(p+1) + x(n);
                obj.buffer(p+1) = y(n);
                p = mod(p+1,del);
                s = y(n) - x(n);
            end
            obj.head = p;
            obj.state = s;
        end
    end
    
end

