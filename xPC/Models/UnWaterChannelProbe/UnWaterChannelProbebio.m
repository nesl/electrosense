function bio=UnWaterChannelProbebio
bio = [];
bio(1).blkName='From Workspace';
bio(1).sigName='';
bio(1).portIdx=0;
bio(1).dim=[1,1];
bio(1).sigWidth=1;
bio(1).sigAddress='&UnWaterChannelProbe_B.FromWorkspace';
bio(1).ndims=2;
bio(1).size=[];

bio(getlenBIO) = bio(1);

bio(2).blkName='Gain';
bio(2).sigName='';
bio(2).portIdx=0;
bio(2).dim=[1,1];
bio(2).sigWidth=1;
bio(2).sigAddress='&UnWaterChannelProbe_B.Gain';
bio(2).ndims=2;
bio(2).size=[];


bio(3).blkName='Gain1';
bio(3).sigName='';
bio(3).portIdx=0;
bio(3).dim=[1,1];
bio(3).sigWidth=1;
bio(3).sigAddress='&UnWaterChannelProbe_B.Gain1';
bio(3).ndims=2;
bio(3).size=[];


bio(4).blkName='Gain2';
bio(4).sigName='';
bio(4).portIdx=0;
bio(4).dim=[1,1];
bio(4).sigWidth=1;
bio(4).sigAddress='&UnWaterChannelProbe_B.Gain2';
bio(4).ndims=2;
bio(4).size=[];


bio(5).blkName='Rate Transition';
bio(5).sigName='';
bio(5).portIdx=0;
bio(5).dim=[1,1];
bio(5).sigWidth=1;
bio(5).sigAddress='&UnWaterChannelProbe_B.RateTransition';
bio(5).ndims=2;
bio(5).size=[];


bio(6).blkName='Rate Transition1';
bio(6).sigName='';
bio(6).portIdx=0;
bio(6).dim=[1,1];
bio(6).sigWidth=1;
bio(6).sigAddress='&UnWaterChannelProbe_B.RateTransition1';
bio(6).ndims=2;
bio(6).size=[];


bio(7).blkName='Rate Transition2';
bio(7).sigName='';
bio(7).portIdx=0;
bio(7).dim=[1,1];
bio(7).sigWidth=1;
bio(7).sigAddress='&UnWaterChannelProbe_B.RateTransition2';
bio(7).ndims=2;
bio(7).size=[];


bio(8).blkName='PCI-6220 AD1/p1';
bio(8).sigName='';
bio(8).portIdx=0;
bio(8).dim=[1,1];
bio(8).sigWidth=1;
bio(8).sigAddress='&UnWaterChannelProbe_B.PCI6220AD1_o1';
bio(8).ndims=2;
bio(8).size=[];


bio(9).blkName='PCI-6220 AD1/p2';
bio(9).sigName='';
bio(9).portIdx=1;
bio(9).dim=[1,1];
bio(9).sigWidth=1;
bio(9).sigAddress='&UnWaterChannelProbe_B.PCI6220AD1_o2';
bio(9).ndims=2;
bio(9).size=[];


bio(10).blkName='PCI-6220 AD1/p3';
bio(10).sigName='';
bio(10).portIdx=2;
bio(10).dim=[1,1];
bio(10).sigWidth=1;
bio(10).sigAddress='&UnWaterChannelProbe_B.PCI6220AD1_o3';
bio(10).ndims=2;
bio(10).size=[];


bio(11).blkName='Random Source';
bio(11).sigName='';
bio(11).portIdx=0;
bio(11).dim=[1,1];
bio(11).sigWidth=1;
bio(11).sigAddress='&UnWaterChannelProbe_B.RandomSource';
bio(11).ndims=2;
bio(11).size=[];


bio(12).blkName='Signal Generator1';
bio(12).sigName='';
bio(12).portIdx=0;
bio(12).dim=[1,1];
bio(12).sigWidth=1;
bio(12).sigAddress='&UnWaterChannelProbe_B.SignalGenerator1';
bio(12).ndims=2;
bio(12).size=[];


function len = getlenBIO
len = 12;

