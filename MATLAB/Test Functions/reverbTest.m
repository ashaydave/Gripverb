
[input,fs] = audioread('Guitar.wav');
input = input(:,1);
output = zeros(length(input),1);

% Tunings
combs = 8;
allPasses = 4;
muted = 0;
fixedGain = 0.015;
scaleWet = 3;
scaleDry = 2;
scaleDamp = 0.4;
scaleRoom = 0.28;
offsetRoom= 0.7;
initialRoom = 0.5;
initialDamp = 0.5;
initialWet = 1/scaleWet;
initialDry = 0;
initialWidth = 1;
initialMode = 0;
freezeMode= 0.5;
stereoSpread = 23;
off = 0;

% lowpass-feedback-comb-filter params
lbcf = [1557 1617 1491 1422 1277 1356 1188 1116];
decay = 0.1; % decay
feedback = 0.98; % feedback, max 0.98 for stability

% allpass params
allPassParams = [225 556 441 341]; % allpass filter frequencies
allpassGain = 0.5;


% initialize comb filter state buffers
comb1 = zeros(lbcf(1),1);
comb2 = zeros(lbcf(2),1);
comb3 = zeros(lbcf(3),1);
comb4 = zeros(lbcf(4),1);
comb5 = zeros(lbcf(5),1);
comb6 = zeros(lbcf(6),1);
comb7 = zeros(lbcf(7),1);
comb8 = zeros(lbcf(8),1);

% initialize allpass filter state buffers
allpass1 = zeros(allPassParams(1),1);
allpass2 = zeros(allPassParams(2),1);
allpass3 = zeros(allPassParams(3),1);
allpass4 = zeros(allPassParams(4),1);

% comb filter write indices
combFilterWriteIndex = ones(8,1);

% comb filter filterstores
filterstore = zeros(8,1);

% allpass filter write indices
allPassWriteIndex = ones(8,1);

% loop through reverberator sample by sample
for i = 1 : length(input)

  in = input(i);
  out = 0;

  % combs in parallel
  [out1,filterstore(1),comb1,combFilterWriteIndex(1)] = comb(comb1,combFilterWriteIndex(1),decay,feedback,in,filterstore(1));
  out = out + out1;
  [out2,filterstore(2),comb2,combFilterWriteIndex(2)] = comb(comb2,combFilterWriteIndex(2),decay,feedback,in,filterstore(2));
  out = out + out2;
  [out3,filterstore(3),comb3,combFilterWriteIndex(3)] = comb(comb3,combFilterWriteIndex(3),decay,feedback,in,filterstore(3));
  out = out + out3;
  [out4,filterstore(4),comb4,combFilterWriteIndex(4)] = comb(comb4,combFilterWriteIndex(4),decay,feedback,in,filterstore(4));
  out = out + out4;
  [out5,filterstore(5),comb5,combFilterWriteIndex(5)] = comb(comb5,combFilterWriteIndex(5),decay,feedback,in,filterstore(5));
  out = out + out5;
  [out6,filterstore(6),comb6,combFilterWriteIndex(6)] = comb(comb6,combFilterWriteIndex(6),decay,feedback,in,filterstore(6));
  out = out + out6;
  [out7,filterstore(7),comb7,combFilterWriteIndex(7)] = comb(comb7,combFilterWriteIndex(7),decay,feedback,in,filterstore(7));
  out = out + out7;
  [out8,filterstore(8),comb8,combFilterWriteIndex(8)] = comb(comb8,combFilterWriteIndex(8),decay,feedback,in,filterstore(8));
  out = out + out8;
  
  % allpasses in series
  [out,allpass1,allPassWriteIndex(1)] = allpass(allpass1,allPassWriteIndex(1),out);
  [out,allpass2,allPassWriteIndex(2)] = allpass(allpass2,allPassWriteIndex(2),out);
  [out,allpass3,allPassWriteIndex(3)] = allpass(allpass3,allPassWriteIndex(3),out);
  [out,allpass4,allPassWriteIndex(4)] = allpass(allpass4,allPassWriteIndex(4),out);

  % apply gain reduction  
  output(i) = out * fixedGain;

end

% output result 20/80 dry-wet mix
mix = (0.5 .* input) + (0.7 .* output);

soundsc(mix,fs);
