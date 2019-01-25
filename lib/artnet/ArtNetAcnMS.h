//Microsoft Specific define statements

#if _MSC_VER > 1000

typedef WCHAR OLECHAR;
          
#define AnsiString							OLECHAR FAR*
                          
#define PipeLibrary							_PipeLibrary
#define NodeLibrary							_NodeLibrary

#define  ArtNetInit(a)						_ArtNetInit(a)
#define  ArtNetEnd							_ArtNetEnd
#define  ArtNetReadWrite(a)					_ArtNetReadWrite(a)

#define ArtNetSendUdp(a,b)					_ArtNetSendUdp(a,b)
#define ArtNetSendUdpPrivate(a,b,c)			_ArtNetSendUdpPrivate(a,b,c)
#define ArtNetSetCallBackUdpReceivePre(a)	_ArtNetSetCallBackUdpReceivePre(a)
#define ArtNetSetCallBackUdpReceivePost(a)	_ArtNetSetCallBackUdpReceivePost(a)
#define ArtNetSetCallBackUdpTransmit(a)		_ArtNetSetCallBackUdpTransmit(a)
#define ArtNetSetCallBackRdmDeviceSelect(a)	_ArtNetSetCallBackRdmDeviceSelect(a)
                                
#define ArtNetCancelCallBack				_ArtNetCancelCallBack
#define ArtNetSetTxPipeUniverse(a,b)		_ArtNetSetTxPipeUniverse(a,b)
#define ArtNetCancelTxPipe(a)				_ArtNetCancelTxPipe(a)
#define ArtNetGetTxPipeUniverse(a)			_ArtNetGetTxPipeUniverse(a)
#define ArtNetSetRxPipeRequestUniverse(a,b) _ArtNetSetRxPipeRequestUniverse(a,b)
#define ArtNetIsRxPipeActive(a)				_ArtNetIsRxPipeActive(a)
#define ArtNetIsTxPipeActive(a)				_ArtNetIsTxPipeActive(a)
#define ArtNetIsPipe0Dongle					_ArtNetIsPipe0Dongle
#define ArtNetGetRxPipeRequestUniverse(a)	_ArtNetGetRxPipeRequestUniverse(a)

#define ArtNetEnumerate						_ArtNetEnumerate
#define ArtNetSoftEnumerate					_ArtNetSoftEnumerate
#define ArtNetAnyArtNetReceived				_ArtNetAnyArtNetReceived

#define ArtNetGetRxPipeIpAddress(a)         _ArtNetGetRxPipeIpAddress(a)
#define ArtNetGetTxPipeIpAddress(a)         _ArtNetGetTxPipeIpAddress(a)
#define ArtNetGetNodeIpAddress(a)			_ArtNetGetNodeIpAddress(a)
#define ArtNetGetNodeIpBindAddress(a)			_ArtNetGetNodeIpBindAddress(a)

#define ArtNetGetRxPipeUniverse(a)			_ArtNetGetRxPipeUniverse(a)

#define ArtNetGetRxPipeStatusUbeaActive(a)  _ArtNetGetRxPipeStatusUbeaActive(a)
#define ArtNetGetTxPipeStatusUbeaActive(a)  _ArtNetGetTxPipeStatusUbeaActive(a)
#define ArtNetGetNodeStatusUbeaActive(a)    _ArtNetGetNodeStatusUbeaActive(a)

#define ArtNetGetRxPipeStatusIndicators(a)  _ArtNetGetRxPipeStatusIndicators(a)
#define ArtNetGetTxPipeStatusIndicators(a)  _ArtNetGetTxPipeStatusIndicators(a)
#define ArtNetGetNodeStatusIndicators(a)    _ArtNetGetNodeStatusIndicators(a)
#define ArtNetGetNodeWebSupport(a)    _ArtNetGetNodeWebSupport(a)

#define ArtNetGetRxPipeStatusAuthority(a)  _ArtNetGetRxPipeStatusAuthority(a)
#define ArtNetGetTxPipeStatusAuthority(a)  _ArtNetGetTxPipeStatusAuthority(a)
#define ArtNetGetNodeStatusAuthority(a)    _ArtNetGetNodeStatusAuthority(a)

#define ArtNetGetRxPipeStatusRdmCapable(a)  _ArtNetGetRxPipeStatusRdmCapable(a)
#define ArtNetGetTxPipeStatusRdmCapable(a)  _ArtNetGetTxPipeStatusRdmCapable(a)
#define ArtNetGetNodeStatusRdmCapable(a)    _ArtNetGetNodeStatusRdmCapable(a)

#define ArtNetGetRxPipeStatusRomBoot(a)     _ArtNetGetRxPipeStatusRomBoot(a)
#define ArtNetGetTxPipeStatusRomBoot(a)     _ArtNetGetTxPipeStatusRomBoot(a)
#define ArtNetGetNodeStatusRomBoot(a)       _ArtNetGetNodeStatusRomBoot(a)

#define ArtNetGetRxPipeUbeaVersion(a)       _ArtNetGetRxPipeUbeaVersion(a)
#define ArtNetGetTxPipeUbeaVersion(a)       _ArtNetGetTxPipeUbeaVersion(a)
#define ArtNetGetNodeUbeaVersion(a)         _ArtNetGetNodeUbeaVersion(a)

#define ArtNetGetRxPipeEstaMan(a)			_ArtNetGetRxPipeEstaMan(a)
#define ArtNetGetTxPipeEstaMan(a)			_ArtNetGetTxPipeEstaMan(a)
#define ArtNetGetNodeEstaMan(a)				_ArtNetGetNodeEstaMan(a)

#define ArtNetGetRxPipeEstaManString(a)     _ArtNetGetRxPipeEstaManString(a)
#define ArtNetGetTxPipeEstaManString(a)     _ArtNetGetTxPipeEstaManString(a)
#define ArtNetGetNodeEstaManString(a)       _ArtNetGetNodeEstaManString(a)
#define ArtNetGetEstaManString(a)			_ArtNetGetEstaManString(a)

#define ArtNetGetRxPipeOemH(a)				_ArtNetGetRxPipeOemH(a)
#define ArtNetGetTxPipeOemH(a)				_ArtNetGetTxPipeOemH(a)
#define ArtNetGetNodeOemH(a)				_ArtNetGetNodeOemH(a)

#define ArtNetGetRxPipeOem(a)				_ArtNetGetRxPipeOem(a)
#define ArtNetGetTxPipeOem(a)				_ArtNetGetTxPipeOem(a)
#define ArtNetGetNodeOem(a)					_ArtNetGetNodeOem(a)

#define ArtNetGetRxPipeOemString(a)         _ArtNetGetRxPipeOemString(a)
#define ArtNetGetTxPipeOemString(a)         _ArtNetGetTxPipeOemString(a)
#define ArtNetGetNodeOemString(a)			_ArtNetGetNodeOemString(a)
#define ArtNetGetOemString(a)				_ArtNetGetOemString(a)
#define ArtNetSwapW(a)						_ArtNetSwapW(a)

#define ArtNetGetNodeRxImplemented(a,b)		_ArtNetGetNodeRxImplemented(a,b)
#define ArtNetGetNodeTxImplemented(a,b)		_ArtNetGetNodeTxImplemented(a,b)

#define ArtNetGetRxPipeRxReceived(a)        _ArtNetGetRxPipeRxReceived(a)
#define ArtNetGetNodeRxReceived(a,b)		_ArtNetGetNodeRxReceived(a,b)

#define ArtNetGetRxPipeRxErrors(a)			_ArtNetGetRxPipeRxErrors(a)
#define ArtNetGetNodeRxErrors(a,b)			_ArtNetGetNodeRxErrors(a,b)

#define ArtNetGetRxPipeRxTest(a)			_ArtNetGetRxPipeRxTest(a)
#define ArtNetGetNodeRxTest(a,b)			_ArtNetGetNodeRxTest(a,b)

#define ArtNetGetRxPipeRxSip(a)				_ArtNetGetRxPipeRxSip(a)
#define ArtNetGetNodeRxSip(a,b)				_ArtNetGetNodeRxSip(a,b)
	
#define ArtNetGetRxPipeRxText(a)			_ArtNetGetRxPipeRxText(a)
#define ArtNetGetNodeRxText(a,b)			_ArtNetGetNodeRxText(a,b)

#define ArtNetGetRxPipeRxDisable(a)         _ArtNetGetRxPipeRxDisable(a)
#define ArtNetGetNodeRxDisable(a,b)			_ArtNetGetNodeRxDisable(a,b)

#define ArtNetGetNodeRxUniverse(a,b)		_ArtNetGetNodeRxUniverse(a,b)
#define ArtNetGetNodeTxUniverse(a,b)		_ArtNetGetNodeTxUniverse(a,b)
#define ArtNetGetNodeSubNet(a)				_ArtNetGetNodeSubNet(a)

#define ArtNetGetNodeTxGood(a,b)			_ArtNetGetNodeTxGood(a,b)
#define ArtNetGetNodeTxMerge(a,b)			_ArtNetGetNodeTxMerge(a,b)
#define ArtNetGetNodeTxLtp(a,b)				_ArtNetGetNodeTxLtp(a,b)
#define ArtNetGetNodeTxShort(a,b)			_ArtNetGetNodeTxShort(a,b)

#define ArtNetGetRxPipeVersionInfoH(a)      _ArtNetGetRxPipeVersionInfoH(a)
#define ArtNetGetTxPipeVersionInfoH(a)		_ArtNetGetTxPipeVersionInfoH(a)
#define ArtNetGetNodeVersionInfoH(a)        _ArtNetGetNodeVersionInfoH(a)

#define ArtNetGetRxPipeVersionInfo(a)       _ArtNetGetRxPipeVersionInfo(a)
#define ArtNetGetTxPipeVersionInfo(a)       _ArtNetGetTxPipeVersionInfo(a)
#define ArtNetGetNodeVersionInfo(a)         _ArtNetGetNodeVersionInfo(a)

#define ArtNetGetRxPipeNumberPorts(a)       _ArtNetGetRxPipeNumberPorts(a)
#define ArtNetGetTxPipeNumberPorts(a)       _ArtNetGetTxPipeNumberPorts(a)
#define ArtNetGetNodeNumberPorts(a)         _ArtNetGetNodeNumberPorts(a)

#define ArtNetGetRxPipeShortName(a)         _ArtNetGetRxPipeShortName(a)
#define ArtNetGetTxPipeShortName(a)         _ArtNetGetTxPipeShortName(a)
#define ArtNetGetNodeShortName(a)			_ArtNetGetNodeShortName(a)

#define ArtNetGetRxPipeLongName(a)			_ArtNetGetRxPipeLongName(a)
#define ArtNetGetTxPipeLongName(a)			_ArtNetGetTxPipeLongName(a)
#define ArtNetGetNodeLongName(a)			_ArtNetGetNodeLongName(a)

#define ArtNetGetRxPipeNodeReport(a)		_ArtNetGetRxPipeNodeReport(a)
#define ArtNetGetTxPipeNodeReport(a)        _ArtNetGetTxPipeNodeReport(a) 
#define ArtNetGetNodeNodeReport(a)			_ArtNetGetNodeNodeReport(a)

#define ArtNetGetRxPipeMacroKeys(a)         _ArtNetGetRxPipeMacroKeys(a)
#define ArtNetGetTxPipeMacroKeys(a)         _ArtNetGetTxPipeMacroKeys(a)
#define ArtNetGetNodeMacroKeys(a)			_ArtNetGetNodeMacroKeys(a)
	
#define ArtNetGetRxPipeRemoteKeys(a)		_ArtNetGetRxPipeRemoteKeys(a)
#define ArtNetGetTxPipeRemoteKeys(a)		_ArtNetGetTxPipeRemoteKeys(a)
#define ArtNetGetNodeRemoteKeys(a)			_ArtNetGetNodeRemoteKeys(a)

#define ArtNetGetRxPipeVideo(a)				_ArtNetGetRxPipeVideo(a)
#define ArtNetGetTxPipeVideo(a)				_ArtNetGetTxPipeVideo(a)
#define ArtNetGetNodeVideo(a)				_ArtNetGetNodeVideo(a)

#define ArtNetGetRxPipeChannelCount(a)		_ArtNetGetRxPipeChannelCount(a)
#define ArtNetGetRxPipePacketCount(a)		_ArtNetGetRxPipePacketCount(a)
#define ArtNetGetTxPipePacketCount(a)		_ArtNetGetTxPipePacketCount(a)
#define ArtNetResetCounters(a)				_ArtNetResetCounters(a)

#define ArtNetSetNodeShortName(a,b)			_ArtNetSetNodeShortName(a,b)
#define ArtNetSetNodeLongName(a,b)			_ArtNetSetNodeLongName(a,b)
#define ArtNetSetNodeSwitches(a,b,c,d,e,f,g,h,i,j,k)	_ArtNetSetNodeSwitches(a,b,c,d,e,f,g,h,i,j,k)
#define ArtNetSetNodeCommand(a,b)			_ArtNetSetNodeCommand(a,b)

#define ArtNetGetRxPipeIndexForIp(a)		_ArtNetGetRxPipeIndexForIp(a)
#define ArtNetGetNodeIndexForIp(a)			_ArtNetGetNodeIndexForIp(a)
#define ArtNetGetNodeIndexForRxPipe(a)		_ArtNetGetNodeIndexForRxPipe(a)
#define ArtNetGetNodeIndexForTxPipe(a)		_ArtNetGetNodeIndexForTxPipe(a)
#define ArtNetGetRxPipeIndexForUniverse(a)	_ArtNetGetRxPipeIndexForUniverse(a)

#define ArtNetShowAboutBox					_ArtNetShowAboutBox
#define ArtNetShowNetworkStatusForm			_ArtNetShowNetworkStatusForm
#define ArtNetShowDataMonitorForm			_ArtNetShowDataMonitorForm
#define ArtNetShowRoutingForm				_ArtNetShowRoutingForm
#define ArtNetShowDriverPopup(x, y)			_ArtNetShowDriverPopup(x, y)
#define ArtNetShowUserIpForm				_ArtNetShowUserIpForm
#define ArtNetSetCallBackPromReceivePre(x)	_ArtNetSetCallBackPromReceivePre(x)

#define ArtNetRecordRouting(a,b)			_ArtNetRecordRouting(a,b)
#define ArtNetSelectRouting(a)				_ArtNetSelectRouting(a)
#define ArtNetGetRoutingName(a)				_ArtNetGetRoutingName(a)
#define ArtNetDeleteRouting(a)				_ArtNetDeleteRouting(a)
#define ArtNetDeleteAllRouting				_ArtNetDeleteAllRouting

#define ArtNetSetTxData(a,b)				_ArtNetSetTxData(a,b)
#define ArtNetSetTxDataGroup(a,b,c)			_ArtNetSetTxDataGroup(a,b,c)
#define ArtNetGetRxData(a)					_ArtNetGetRxData(a)
#define ArtNetClearDataBuffer(a)			_ArtNetClearDataBuffer(a)

//New funtcions for RMD
#define ArtNetForceNodeDiscovery(a,b)		_ArtNetForceNodeDiscovery(a,b)

#define RdmDeviceGetPtr(a,b,c)				_RdmDeviceGetPtr(a,b,c)
#define RdmDeviceUidMatch(a,b)				_RdmDeviceUidMatch(a,b)
#define RdmDeviceDoesUidExist(a)			_RdmDeviceDoesUidExist(a)

#define RdmDeviceGetFirstPtr(a,b)			_RdmDeviceGetFirstPtr(a,b)
#define RdmDeviceGetNextPtr(a)				_RdmDeviceGetNextPtr(a)
#define RdmDeviceGetIndexPtr(a,b,c)			_RdmDeviceGetIndexPtr(a,b,c)
#define RdmDeviceAdd(a,b,c)					_RdmDeviceAdd(a,b,c)
#define RdmDeviceInvalidate(a)				_RdmDeviceInvalidate(a)
#define RdmDeviceInvalidatePort(a,b)		_RdmDeviceInvalidatePort(a,b)

#define RdmDeviceAddRootSensor(a,b)			_RdmDeviceAddRootSensor(a,b)
#define RdmDeviceDeleteSensors(a)			_RdmDeviceDeleteSensors(a)
#define RdmDeviceInvalidateSensors(a)		_RdmDeviceInvalidateSensors(a)

#define RdmDeviceGetRootSensorCount(a,b,c)	_RdmDeviceGetRootSensorCount(a,b,c)
#define RdmDeviceGetRootSensorCountPtr(a)	_RdmDeviceGetRootSensorCountPtr(a)

#define RdmDeviceGetRootSensorValueString(a,b,c,d,e)		_RdmDeviceGetRootSensorValueString(a,b,c,d,e)
#define RdmDeviceGetRootSensorValueStringBySensorPtr(a,b)	_RdmDeviceGetRootSensorValueStringBySensorPtr(a,b)

#define RdmDeviceGetRootSensorValid(a,b,c,d)				_RdmDeviceGetRootSensorValid(a,b,c,d)

#define RdmDeviceGetRootSensorWarning(a,b,c,d)				_RdmDeviceGetRootSensorWarning(a,b,c,d)
#define RdmDeviceGetRootSensorWarningPtr(a,b)				_RdmDeviceGetRootSensorWarningPtr(a,b)
	
#define RdmDeviceGetRootSensorError(a,b,c,d)				_RdmDeviceGetRootSensorError(a,b,c,d)
#define RdmDeviceGetRootSensorErrorPtr(a,b)					_RdmDeviceGetRootSensorErrorPtr(a,b)

#define RdmDeviceGetRootSensor(a,b,c,d)		_RdmDeviceGetRootSensor(a,b,c,d)
#define RdmDeviceGetRootSensorPtr(a,b)		_RdmDeviceGetRootSensorPtr(a,b)

#define RdmDeviceGetAnySensorWarning(a,b,c)	_RdmDeviceGetAnySensorWarning(a,b,c)	
#define RdmDeviceGetAnySensorWarningPtr(a)	_RdmDeviceGetAnySensorWarningPtr(a)

#define RdmDeviceGetAnySensorError(a,b,c)	_RdmDeviceGetAnySensorError(a,b,c)
#define RdmDeviceGetAnySensorErrorPtr(a)	_RdmDeviceGetAnySensorErrorPtr(a)

#define RdmDeviceAnyDevices(a,b)			_RdmDeviceAnyDevices(a,b)

#define RdmDeviceGetDeviceCount(a,b)		_RdmDeviceGetDeviceCount(a,b)

#define RdmDeviceRequestTod(a)				_RdmDeviceRequestTod(a)
#define RdmDeviceArmAllGets(a)				_RdmDeviceArmAllGets(a)		

#define RdmDeviceArtRdmTemplate(a,b,c,d)	_RdmDeviceArtRdmTemplate(a,b,c,d)
#define RdmDeviceArtRdmSend(a,b,c,d)		_RdmDeviceArtRdmSend(a,b,c,d)

#define RdmDeviceGetValid(a,b,c)			_RdmDeviceGetValid(a,b,c)
#define RdmDeviceGetValidPtr(a)				_RdmDeviceGetValidPtr(a)
#define RdmDeviceGetApplicationRedraw(a,b,c)	_RdmDeviceGetApplicationRedraw(a,b,c)
#define RdmDeviceGetApplicationRedrawPtr(a)	_RdmDeviceGetApplicationRedrawPtr(a)
#define RdmDeviceGetAddToList(a,b,c)		_RdmDeviceGetAddToList(a,b,c)
#define RdmDeviceGetAnyAddToList(a,b)		_RdmDeviceGetAnyAddToList(a,b)
#define RdmDeviceGetModelName(a,b,c)		_RdmDeviceGetModelName(a,b,c)
#define RdmDeviceGetModelNamePtr(a)			_RdmDeviceGetModelNamePtr(a)

#define RdmDeviceGetManufacturerName(a,b,c)	_RdmDeviceGetManufacturerName(a,b,c)
#define RdmDeviceGetManufacturerNamePtr(a)	_RdmDeviceGetManufacturerNamePtr(a)

#define RdmDeviceGetDeviceLabel(a,b,c)		_RdmDeviceGetDeviceLabel(a,b,c)
#define RdmDeviceSetDeviceLabel(a,b,c,d)	_RdmDeviceSetDeviceLabel(a,b,c,d)
#define RdmDeviceGetStartAddress(a,b,c)		_RdmDeviceGetStartAddress(a,b,c)
#define RdmDeviceSetStartAddress(a,b,c,d)	_RdmDeviceSetStartAddress(a,b,c,d)
#define RdmDeviceSetStartAddressPtr(a,b)	_RdmDeviceSetStartAddressPtr(a,b)

#define RdmDeviceGetFootprint(a,b,c)		_RdmDeviceGetFootprint(a,b,c)
#define RdmDeviceGetSubDeviceCount(a,b,c)	_RdmDeviceGetSubDeviceCount(a,b,c)
#define RdmDeviceGetCountDeviceHours(a,b,c)	_RdmDeviceGetCountDeviceHours(a,b,c)
#define RdmDeviceGetCountLampHours(a,b,c)	_RdmDeviceGetCountLampHours(a,b,c)
#define RdmDeviceGetCountLampStrikes(a,b,c)	_RdmDeviceGetCountLampStrikes(a,b,c)
#define RdmDeviceGetDeviceId(a,b,c)			_RdmDeviceGetDeviceId(a,b,c)

#define RdmDeviceGetSoftwareStatus(a,b,c)	_RdmDeviceGetSoftwareStatus(a,b,c)
#define RdmDeviceGetSoftwareVersionString(a,b,c)	_RdmDeviceGetSoftwareVersionString(a,b,c)

#define RdmDeviceGetSoftwareVersionStringPtr(a)		_RdmDeviceGetSoftwareVersionStringPtr(a)

#define RdmDeviceGetUid(a,b,c)				_RdmDeviceGetUid(a,b,c)
#define RdmDeviceGetUidString(a,b,c)		_RdmDeviceGetUidString(a,b,c)
#define RdmDeviceGetUidStringShort(a,b,c)	_RdmDeviceGetUidStringShort(a,b,c)	
#define RdmDeviceSetUidStringShort(a,b,c,d)	_RdmDeviceSetUidStringShort(a,b,c,d)
#define RdmDeviceSetLocate(a,b,c,d)			_RdmDeviceSetLocate(a,b,c,d)
#define RdmDeviceSetLocatePtr(a,b)			_RdmDeviceSetLocatePtr(a,b)

#define RdmDeviceSetSelfTest(a,b,c,d)		_RdmDeviceSetSelfTest(a,b,c,d)
#define RdmDeviceSetResetDevice(a,b,c)		_RdmDeviceSetResetDevice(a,b,c)
#define RdmDeviceSetFactoryDefaults(a,b,c)	_RdmDeviceSetFactoryDefaults(a,b,c)
#define RdmDeviceSetExitCommand(a,b,c)		_RdmDeviceSetExitCommand(a,b,c)
#define RdmDeviceSetDisplayLevel(a,b,c,d)	_RdmDeviceSetDisplayLevel(a,b,c,d)
#define RdmDeviceSetDisplayLevelPtr(a,b)	_RdmDeviceSetDisplayLevelPtr(a,b)

#define RdmDeviceSetDisplayInvert(a,b,c,d)	_RdmDeviceSetDisplayInvert(a,b,c,d)
#define RdmDeviceSetLampState(a,b,c,d)		_RdmDeviceSetLampState(a,b,c,d)
#define RdmDeviceSetFastPoll(a,b,c,d)		_RdmDeviceSetFastPoll(a,b,c,d)

#define RdmDeviceGetLastBlockSize(a,b,c)		_RdmDeviceGetLastBlockSize(a,b,c)
#define RdmDeviceGetFirmwareReplyType(a,b,c)	_RdmDeviceGetFirmwareReplyType(a,b,c)
#define RdmDeviceClearFirmwareReplyType(a,b,c)	_RdmDeviceClearFirmwareReplyType(a,b,c)

#define TextFromRdm(a,b,c)					_TextFromRdm(a,b,c)

#define RdmDeviceConvertUidStringToStructure(a,b)	_RdmDeviceConvertUidStringToStructure(a,b)
#define RdmDeviceConvertStructureToUidString(a,b)	_RdmDeviceConvertStructureToUidString(a,b)

#define ArtNetGetMyIpAddress				_ArtNetGetMyIpAddress
#define WordFromRdm(a,b)					_WordFromRdm(a,b)
#define LongWordFromRdm(a,b)				_LongWordFromRdm(a,b)
#define ByteFromRdm(a,b)					_ByteFromRdm(a,b)

#define ArtNetIpProgPollRequest(a)			_ArtNetIpProgPollRequest(a)
//End of new functions

#define DongleResetRxCounters				_DongleResetRxCounters
#define DongleSetRxStartCode(a)				_DongleSetRxStartCode(a)
#define DongleSetTxStartCode(a)				_DongleSetTxStartCode(a)
#define DongleGetRxStartCode				_DongleGetRxStartCode
#define DongleGetTxStartCode				_DongleGetTxStartCode
#define DongleSetTxBreakTime(a)				_DongleSetTxBreakTime(a)
#define DongleSetTxMabTime(a)				_DongleSetTxMabTime(a)
#define DongleGetFirmwareRevision			_DongleGetFirmwareRevision
#define DongleGetType						_DongleGetType
#define DongleGetChannelCount				_DongleGetChannelCount
#define DongleGetBreakTime					_DongleGetBreakTime
#define DongleGetMabTime					_DongleGetMabTime
#define DongleGetPeriod						_DongleGetPeriod
#define DongleGetOverrunErrorCount			_DongleGetOverrunErrorCount
#define DongleGetFramingErrorCount			_DongleGetFramingErrorCount
#define DongleGetStartCodeErrorCount		_DongleGetStartCodeErrorCount
#define DongleGetPacketCount				_DongleGetPacketCount
#define DongleSetAux1(a)					_DongleSetAux1(a)
#define DongleSetAux2(a)					_DongleSetAux2(a)
#define DongleSetAux3(a)					_DongleSetAux3(a)
#define DongleSetAux4(a)					_DongleSetAux4(a)
#define DongleSetAux5(a)					_DongleSetAux5(a)
#define DongleGetDLLRevision				_DongleGetDLLRevision
#define DongleGetVxDRevision				_DongleGetVxDRevision
#define DongleGetFrequency					_DongleGetFrequency
#define DongleSetTransferCount(a)			_DongleSetTransferCount(a)
#define DongleGetTransferCount				_DongleGetTransferCount
#define DongleGetPortAddress				_DongleGetPortAddress
#define DongleSetLoopOn						_DongleSetLoopOn
#define DongleSetMergeOn					_DongleSetMergeOn
#define DongleSetLoopOff					_DongleSetLoopOff
#define DongleSetAux(a,b)					_DongleSetAux(a,b)

#endif
