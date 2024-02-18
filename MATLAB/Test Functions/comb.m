function [out,filterstore,buffer,index] = comb(buffer,index,damping,feedback,input,filterstore)

out = buffer(index);
filterstore = (out*(1-damping)) + (filterstore*damping);
buffer(index) = input + (filterstore*feedback);

% circularly wrap index
if ((index + 1) > length(buffer))
    index = 1;
else
    index = index + 1;
end

