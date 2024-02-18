function [out,buffer,index] = allpass(buffer,index,in)

gain= 0.5;

bufferOut = buffer(index);
out = -1*in + bufferOut;
buffer(index) = in + (bufferOut*gain);

if ((index + 1) > length(buffer))
    index = 1;
else
    index = index + 1;
end