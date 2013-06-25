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
    ;% Auto data (UnWaterChannelProbe3_P)
    ;%
      section.nData     = 34;
      section.data(34)  = dumData; %prealloc
      
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P1_Size
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P1
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 2;
	
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P2_Size
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 5;
	
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P2
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 7;
	
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P3_Size
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 10;
	
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P3
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 12;
	
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P4_Size
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 15;
	
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P4
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 17;
	
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P5_Size
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 18;
	
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P5
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 20;
	
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P6_Size
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 21;
	
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P6
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 23;
	
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P7_Size
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 24;
	
	  ;% UnWaterChannelProbe3_P.PCI6220AD1_P7
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 26;
	
	  ;% UnWaterChannelProbe3_P.Gain_Gain
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 27;
	
	  ;% UnWaterChannelProbe3_P.Gain2_Gain
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 28;
	
	  ;% UnWaterChannelProbe3_P.Gain3_Gain
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 29;
	
	  ;% UnWaterChannelProbe3_P.PCI6713DA1_P1_Size
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 30;
	
	  ;% UnWaterChannelProbe3_P.PCI6713DA1_P1
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 32;
	
	  ;% UnWaterChannelProbe3_P.PCI6713DA1_P2_Size
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 33;
	
	  ;% UnWaterChannelProbe3_P.PCI6713DA1_P2
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 35;
	
	  ;% UnWaterChannelProbe3_P.PCI6713DA1_P3_Size
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 36;
	
	  ;% UnWaterChannelProbe3_P.PCI6713DA1_P3
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 38;
	
	  ;% UnWaterChannelProbe3_P.PCI6713DA1_P4_Size
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 39;
	
	  ;% UnWaterChannelProbe3_P.PCI6713DA1_P4
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 41;
	
	  ;% UnWaterChannelProbe3_P.PCI6713DA1_P5_Size
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 42;
	
	  ;% UnWaterChannelProbe3_P.PCI6713DA1_P5
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 44;
	
	  ;% UnWaterChannelProbe3_P.PCI6713DA1_P6_Size
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 45;
	
	  ;% UnWaterChannelProbe3_P.PCI6713DA1_P6
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 47;
	
	  ;% UnWaterChannelProbe3_P.RandomSource_MinRTP
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 48;
	
	  ;% UnWaterChannelProbe3_P.RandomSource_MaxRTP
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 49;
	
	  ;% UnWaterChannelProbe3_P.Gain1_Gain
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 50;
	
	  ;% UnWaterChannelProbe3_P.SignalGenerator1_Amplitude
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 51;
	
	  ;% UnWaterChannelProbe3_P.SignalGenerator1_Frequency
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 52;
	
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
    ;% Auto data (UnWaterChannelProbe3_B)
    ;%
      section.nData     = 14;
      section.data(14)  = dumData; %prealloc
      
	  ;% UnWaterChannelProbe3_B.PCI6220AD1_o1
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% UnWaterChannelProbe3_B.PCI6220AD1_o2
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% UnWaterChannelProbe3_B.PCI6220AD1_o3
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% UnWaterChannelProbe3_B.RateTransition1
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% UnWaterChannelProbe3_B.Gain
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% UnWaterChannelProbe3_B.RateTransition2
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% UnWaterChannelProbe3_B.Gain2
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% UnWaterChannelProbe3_B.RateTransition3
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% UnWaterChannelProbe3_B.Gain3
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% UnWaterChannelProbe3_B.FromWorkspace
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% UnWaterChannelProbe3_B.RateTransition
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 10;
	
	  ;% UnWaterChannelProbe3_B.RandomSource
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 11;
	
	  ;% UnWaterChannelProbe3_B.Gain1
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 12;
	
	  ;% UnWaterChannelProbe3_B.SignalGenerator1
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 13;
	
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
    ;% Auto data (UnWaterChannelProbe3_DWork)
    ;%
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% UnWaterChannelProbe3_DWork.RandomSource_STATE_DWORK
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% UnWaterChannelProbe3_DWork.PCI6713DA1_RWORK
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 35;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% UnWaterChannelProbe3_DWork.PCI6220AD1_PWORK
	  section.data(1).logicalSrcIdx = 2;
	  section.data(1).dtTransOffset = 0;
	
	  ;% UnWaterChannelProbe3_DWork.FromWorkspace_PWORK.TimePtr
	  section.data(2).logicalSrcIdx = 3;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% UnWaterChannelProbe3_DWork.RandomSource_SEED_DWORK
	  section.data(1).logicalSrcIdx = 4;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% UnWaterChannelProbe3_DWork.PCI6220AD1_IWORK
	  section.data(1).logicalSrcIdx = 5;
	  section.data(1).dtTransOffset = 0;
	
	  ;% UnWaterChannelProbe3_DWork.FromWorkspace_IWORK.PrevIndex
	  section.data(2).logicalSrcIdx = 6;
	  section.data(2).dtTransOffset = 41;
	
	  ;% UnWaterChannelProbe3_DWork.PCI6713DA1_IWORK
	  section.data(3).logicalSrcIdx = 7;
	  section.data(3).dtTransOffset = 42;
	
	  ;% UnWaterChannelProbe3_DWork.SFunction_IWORK.AcquireOK
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


  targMap.checksum0 = 932112434;
  targMap.checksum1 = 1444229945;
  targMap.checksum2 = 2008472164;
  targMap.checksum3 = 3175955013;

