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
    ;% Auto data (xpcosc_P)
    ;%
      section.nData     = 33;
      section.data(33)  = dumData; %prealloc
      
	  ;% xpcosc_P.Integrator1_IC
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% xpcosc_P.PCI6221AD_P1_Size
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% xpcosc_P.PCI6221AD_P1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 3;
	
	  ;% xpcosc_P.PCI6221AD_P2_Size
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 4;
	
	  ;% xpcosc_P.PCI6221AD_P2
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 6;
	
	  ;% xpcosc_P.PCI6221AD_P3_Size
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 7;
	
	  ;% xpcosc_P.PCI6221AD_P3
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 9;
	
	  ;% xpcosc_P.PCI6221AD_P4_Size
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 10;
	
	  ;% xpcosc_P.PCI6221AD_P4
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 12;
	
	  ;% xpcosc_P.PCI6221AD_P5_Size
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 13;
	
	  ;% xpcosc_P.PCI6221AD_P5
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 15;
	
	  ;% xpcosc_P.PCI6221AD_P6_Size
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 16;
	
	  ;% xpcosc_P.PCI6221AD_P6
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 18;
	
	  ;% xpcosc_P.PCI6221AD_P7_Size
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 19;
	
	  ;% xpcosc_P.PCI6221AD_P7
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 21;
	
	  ;% xpcosc_P.SignalGenerator_Amplitude
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 22;
	
	  ;% xpcosc_P.SignalGenerator_Frequency
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 23;
	
	  ;% xpcosc_P.PCI6713DA_P1_Size
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 24;
	
	  ;% xpcosc_P.PCI6713DA_P1
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 26;
	
	  ;% xpcosc_P.PCI6713DA_P2_Size
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 27;
	
	  ;% xpcosc_P.PCI6713DA_P2
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 29;
	
	  ;% xpcosc_P.PCI6713DA_P3_Size
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 30;
	
	  ;% xpcosc_P.PCI6713DA_P3
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 32;
	
	  ;% xpcosc_P.PCI6713DA_P4_Size
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 33;
	
	  ;% xpcosc_P.PCI6713DA_P4
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 35;
	
	  ;% xpcosc_P.PCI6713DA_P5_Size
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 36;
	
	  ;% xpcosc_P.PCI6713DA_P5
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 38;
	
	  ;% xpcosc_P.PCI6713DA_P6_Size
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 39;
	
	  ;% xpcosc_P.PCI6713DA_P6
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 41;
	
	  ;% xpcosc_P.Gain_Gain
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 42;
	
	  ;% xpcosc_P.Integrator_IC
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 43;
	
	  ;% xpcosc_P.Gain1_Gain
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 44;
	
	  ;% xpcosc_P.Gain2_Gain
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 45;
	
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
    ;% Auto data (xpcosc_B)
    ;%
      section.nData     = 10;
      section.data(10)  = dumData; %prealloc
      
	  ;% xpcosc_B.Integrator1
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% xpcosc_B.PCI6221AD
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% xpcosc_B.RateTransition1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% xpcosc_B.SignalGenerator
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% xpcosc_B.RateTransition
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% xpcosc_B.Gain
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% xpcosc_B.Integrator
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% xpcosc_B.Gain1
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% xpcosc_B.Gain2
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% xpcosc_B.Sum
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
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
    nTotSects     = 3;
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
    ;% Auto data (xpcosc_DWork)
    ;%
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% xpcosc_DWork.PCI6713DA_RWORK
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% xpcosc_DWork.PCI6221AD_PWORK
	  section.data(1).logicalSrcIdx = 1;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% xpcosc_DWork.PCI6221AD_IWORK
	  section.data(1).logicalSrcIdx = 2;
	  section.data(1).dtTransOffset = 0;
	
	  ;% xpcosc_DWork.PCI6713DA_IWORK
	  section.data(2).logicalSrcIdx = 3;
	  section.data(2).dtTransOffset = 41;
	
	  ;% xpcosc_DWork.SFunction_IWORK.AcquireOK
	  section.data(3).logicalSrcIdx = 4;
	  section.data(3).dtTransOffset = 43;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
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


  targMap.checksum0 = 1235351435;
  targMap.checksum1 = 4143988505;
  targMap.checksum2 = 362576123;
  targMap.checksum3 = 1068881914;

