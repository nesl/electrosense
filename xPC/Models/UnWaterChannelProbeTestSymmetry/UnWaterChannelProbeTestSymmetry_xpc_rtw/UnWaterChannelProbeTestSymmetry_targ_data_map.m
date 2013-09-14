  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (UnWaterChannelProbeTestSymmetry_P)
    ;%
      section.nData     = 38;
      section.data(38)  = dumData; %prealloc
      
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P1_Size
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P1
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 2;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P2_Size
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 9;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P2
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 11;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P3_Size
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 18;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P3
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 20;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P4_Size
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 27;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P4
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 29;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P5_Size
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 30;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P5
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 32;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P6_Size
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 33;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P6
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 35;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P7_Size
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 36;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6220AD1_P7
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 38;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.Gain_Gain
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 39;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.Gain2_Gain
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 40;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.Gain3_Gain
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 41;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.Gain4_Gain
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 42;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.Gain5_Gain
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 43;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.Gain6_Gain
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 44;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.Gain7_Gain
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 45;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.SignalGenerator1_Amplitude
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 46;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.SignalGenerator1_Frequency
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 47;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P1_Size
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 48;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P1
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 50;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P2_Size
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 51;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P2
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 53;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P3_Size
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 54;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P3
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 56;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P4_Size
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 57;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P4
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 59;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P5_Size
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 60;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P5
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 62;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P6_Size
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 63;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.PCI6713DA1_P6
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 65;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.RandomSource_MinRTP
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 66;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.RandomSource_MaxRTP
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 67;
	
	  ;% UnWaterChannelProbeTestSymmetry_P.Gain1_Gain
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 68;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (UnWaterChannelProbeTestSymmetry_B)
    ;%
      section.nData     = 26;
      section.data(26)  = dumData; %prealloc
      
	  ;% UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o1
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o2
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o3
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o4
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o5
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o6
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.PCI6220AD1_o7
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.RateTransition1
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.Gain
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.RateTransition2
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.Gain2
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.RateTransition3
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.Gain3
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.RateTransition4
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.Gain4
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 14;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.RateTransition5
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 15;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.Gain5
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 16;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.RateTransition6
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 17;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.Gain6
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 18;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.RateTransition7
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 19;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.Gain7
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 20;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.SignalGenerator1
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 21;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.RateTransition
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 22;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.FromWorkspace
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 23;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.RandomSource
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 24;
	
	  ;% UnWaterChannelProbeTestSymmetry_B.Gain1
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 25;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 4;
    sectIdxOffset = 1;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (UnWaterChannelProbeTestSymmetry_DWork)
    ;%
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% UnWaterChannelProbeTestSymmetry_DWork.RandomSource_STATE_DWORK
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% UnWaterChannelProbeTestSymmetry_DWork.PCI6713DA1_RWORK
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 35;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% UnWaterChannelProbeTestSymmetry_DWork.PCI6220AD1_PWORK
	  section.data(1).logicalSrcIdx = 2;
	  section.data(1).dtTransOffset = 0;
	
	  ;% UnWaterChannelProbeTestSymmetry_DWork.FromWorkspace_PWORK.TimePtr
	  section.data(2).logicalSrcIdx = 3;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% UnWaterChannelProbeTestSymmetry_DWork.RandomSource_SEED_DWORK
	  section.data(1).logicalSrcIdx = 4;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% UnWaterChannelProbeTestSymmetry_DWork.PCI6220AD1_IWORK
	  section.data(1).logicalSrcIdx = 5;
	  section.data(1).dtTransOffset = 0;
	
	  ;% UnWaterChannelProbeTestSymmetry_DWork.PCI6713DA1_IWORK
	  section.data(2).logicalSrcIdx = 6;
	  section.data(2).dtTransOffset = 41;
	
	  ;% UnWaterChannelProbeTestSymmetry_DWork.SFunction_IWORK.AcquireOK
	  section.data(3).logicalSrcIdx = 7;
	  section.data(3).dtTransOffset = 43;
	
	  ;% UnWaterChannelProbeTestSymmetry_DWork.FromWorkspace_IWORK.PrevIndex
	  section.data(4).logicalSrcIdx = 8;
	  section.data(4).dtTransOffset = 44;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 1807537776;
  targMap.checksum1 = 2602500741;
  targMap.checksum2 = 635672932;
  targMap.checksum3 = 11205098;

