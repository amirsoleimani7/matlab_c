// ======================================
// Register_Map_Define.vh
// Shared register definitions
// ======================================

`ifndef REGISTER_MAP_DEFINE_VH
`define REGISTER_MAP_DEFINE_VH



// we start broadcast address from 24'hFFFFFFE0 to 24'hFFFFFFFF
`define GenUnitCode     10'h002 //{8'h00,2'b10}
/// 2 bit code in address definition 
`define PS_CODE 2'b11  // all broadcast address 
`define GEN_CODE 2'b10
`define CUR_LOAD_CODE 2'b01
`define CTRL_CODE 2'b00
//////////////// Global address
// global address and corresponding local addresses :  lower range of machin address is used for shre global and locals
	//////////////////
`define 	TOPLOGY_CONF_GLBADR		24'hFFFE01// 9'h001// ps -<system controller :{generator_numbers[5:0],load_numbers[5:0],bus_num[7:0],line_num[7:0],svc_num[3:0]}
`define 	INITIALIZE_DONE_GLBCMD	24'hFFFE02// 9'h002
`define 	NEW_CONFIG_GLBCMD		24'hFFFE03// 9'h003
`define 	RESET_CONFIG_GLBCMD		24'hFFFE04// 9'h004

`define 	FLAG1_START_GLBCMD		24'hFFFE05// 9'h005
`define 	FLAG2_START_GLBCMD		24'hFFFE06// 9'h006
`define 	PREDICT_UPD_GLBCMD		24'hFFFE07// 9'h007
`define 	CORRECT_UPD_GLBCMD		24'hFFFE08// 9'h008


`define  	H_SOL_GLBADR		24'hFFFE09// 9'h009//{BROADCAST_TYPE[14:0],H_SOL_GLBADR[8:0]} 
`define 	BASRAD_GLBADR		24'hFFFE0A// 9'h00A
`define 	BASMVA_GLBADR		24'hFFFE0B// 9'h00B
`define 	SYS_FREQ_GLBADR		24'hFFFE0C// 9'h00C

`define 	BUS_CONF_THETA_BASADR			24'hFFFF01 // 9'h101//{bus_num[7:0], theta[15:0]}
`define 	BUS_CONF_VOLTAGE_BASEADR		24'hFFFF05// 9'h105 //{bus_num[7:0],busv[15:0]}

`define 	PM_SIG_GLBADR		24'hFFFF21// 9'h121
`define 	EXC_SIG_GLBADR		24'hFFFF22// 9'h122
`define 	TG_SIG_GLBADR		24'hFFFF23// 9'h123
`define 	SVC_SIG_GLBADR		24'hFFFF24// 9'h124


`define 	ISIM_START_Step1_GLBCMD	24'hFFFF09// 9'h109
`define 	ISIM_START_Step2_GLBCMD	24'hFFFF0A// 9'h10A
`define 	ISIM_START_Step3_GLBCMD	24'hFFFF0B// 9'h10B
`define 	NCLOAD_START_GLBCMD		24'hFFFF0C // 9'h10C



//*********NC_Load address 
`define 	SYSTEM_LOG_CONF_GLBADR	24'h1FFF31//9'h131
`define 	NC_LOAD_LOW_THRESHOLD	24'h1FFF32//9'h132
`define 	NC_LOAD_VNC0			24'h1FFF33//9'h133
`define 	NC_LOAD_VNC_BUSNUM		24'h1FFF34//9'h134





		

 		
//`define 	H_SOL_GLBADR	24'hFFFF36= 
//parameter  BROADCAST_TYPE  = 15'h7fff  // 24 -9 =15 bit 

`define 	H_SOL_LOCADR	9'h009
`define 	BASRAD_LOCADR	9'h00A
`define 	BASMVA_LOCADR	9'h00B
`define 	SYS_FREQ_LOCADR	9'h00C

`define 	PM_SIG_LOCADR	9'h121
`define 	EXC_SIG_LOCADR	9'h122
`define 	TG_SIG_LOCADR	9'h123
`define 	SVC_SIG_LOCADR	9'h124



`define  RESET_CONFIG_LOCMD		9'h004
`define  MAC_FLAG1_START_LOCMD	9'h005
`define  MAC_FLAG2_START_LOCMD	9'h006
`define  PREDICT_UPD_LOCMD		9'h007
`define  CORRECT_UPD_LOCMD		9'h008

// new define added after design phase // 4 bit command is defined for each command

`define 		PS_GET_STAUS_GLBCMD	    24'hFFFF0D
`define 		SYSCTRL_GET_STAUS_DATA	24'hFFFF0E

// Y tables 8bit address 24 bit data is written in memory by pS via AXI Interface 
// 8 bit address is read and send to system controller 

// switch address


`define 	GenUnit_OUT_PSI_CODE	24'hFFFE21//9'h021
`define 	GET_ENGIN_indx_PSI		24'hFFFE22//9'h022
`define 	ANS_ENGIN_indx_PSI		24'hFFFE23//9'h023
`define 	ENGIN_PSI_REPORT_END	24'hFFFE24//9'h024
`define 	CURENT_REPORT_END		24'hFFFE25//9'h025// shows end of current process ang log 
`define 	GET_READY_STATUS		24'hFFFE26//9'h026
`define 	SW_READY_STATUS			24'hFFFE27//9'h027
//`define 	SET_GENERATOR_NUMBER	24'hFFFE28
//`define 	SET_LOAD_NUMBER     	24'hFFFE29
//`define 	SET_BUS_NUMBER      	24'hFFFE2A
//`define 	SET_GENBUS_ORDER    	24'hFFFE2B

 	///////////////////////////
	//each  generation unit adress  tables star with 9'h1xx
// GEN_CODE 2'b10
	// single registers satrt with 9'h0xx
`define  GENERATION_UNIT_CONF_LOCADR	9'h010
`define  MAC_ANG_LOCADR	9'h012
`define  MAC_REF_LOCADR	9'h013
`define  MAC_CON_LOC_OFFSET	9'h120
`define  MAC_CON_INV_LOC_OFFSET	9'h140
`define  MAC_POT_LOC_OFFSET	9'h160
`define  MAC_EDPRIME_LOCADR	9'h014
`define  MAC_EQPRIME_LOCADR	9'h015
`define  MAC_PMECH_LOCADR	9'h016
  	
`define  EXC_CON_LOC_OFFSET	9'h180
`define  EXC_POT_LOC_OFFSET	9'h1A0
`define  EXC_CON_INV_LOC_OFFSET	9'h1C0

`define  PSS_CON_LOC_OFFSET	9'h1E0
`define  PSS_POT_LOC_OFFSET	9'h180
`define  PSS_CON_INV_LOC_OFFSET	9'h190
`define  PSS_PSS1_LOCADR	9'h029

`define  V_E_EXC_GLBADDR	9'h031
`define  I_LAST_EXC_GLBADDR	9'h032
`define  TG_CON_LOC_OFFSET	9'h1A0
`define  TG_CON_INV_LOC_OFFSET	9'h1B0
`define  TG_POT_LOC_OFFSET	9'h1C0
`define  TG1_LOCADR	9'h036
`define  TG2_LOCADR	9'h037
`define  TG3_LOCADR	9'h038

`define  EXC_V_R_LOCADR	9'h040
`define  EXC_V_AS_LOCADR	9'h041
`define  EXC_V_RTR_LOCADR	9'h042
 // common GLB LOC Address :




 // 9'h01x
`define  PSS_FLAG1_START_LOCMD	9'h014
`define  EXC_FLAG1_START_LOCMD	9'h015
`define  TG_FLAG1_START_LOCMD	9'h016
//`define  MAC_FLAG2_START_LOCMD	9'h017
`define  PSS_FLAG2_START_LOCMD	9'h018
`define  EXC_FLAG2_START_LOCMD	9'h019
`define  TG_FLAG2_START_LOCMD	9'h01A










`define  MAC_ANG_SIN_LOCADR	9'h053
`define  MAC_ANG_COS_LOCADR	9'h054
//`define  MAC_PSI_RE_LOCADR	9'h055
//`define  MAC_PSI_IM_LOCADR	9'h056
`define  MAC_PSI_LOCADR	9'h057
 	
`define  MAC_PSIKD_LOCADR	9'h060
`define  MAC_PSIKQ_LOCADR	9'h061
`define  MAC_SPD_LOCADR	9'h062
`define  MAC_ETERM_LOCADR	9'h063
`define  EXC_PELEC_LOCADR	9'h064
`define  EXC_QELEC_LOCADR	9'h065
`define  EXC_VEX_LOCADR	9'h066
`define  TG_PMECH_LOCADR	9'h067
	
`define  PSS_PSS_OUT_LOCADR	9'h070
// current to machin controller :

`define  BUS_V_LOCADR		9'h074
`define  THETA_LOCADR		9'h075
`define  CUR_RE_LOCADR		9'h076
`define  CUR_IM_LOCADR		9'h077


`define  EXC_REPORT_DONE	9'h082
`define  TG_REPORT_DONE		9'h083

// curent Address interface with system controller 
// current data manager interface via system controller ( short code)
//  curr_Blk_ID =0 [23:9] =0 startaddr = 24'h00000


`define  CUR_PSI_LOCADR		9'h011 // 9
//`define  CUR_PSI_IM_LOCADR		8'h12

// systemcontroller _ datamanagement_current   8 bit send/receive interface
`define 		GET_YBUS_CONFIG			9'h001 //system_controller -> DatamAnagement
`define 		END_YBUS_CONFIG			9'h111//24'h020000 // DatamAnagement -> system_controller//// sysctrl format is used for y=this command



//system controller and current/bus/load communicatiion 
// these information arepassed through data manager as packed addr,data command 
// current data manager interface via system controller ( short code)
//address format : 8 bit contentcode + 2 bit srccode(2'b01) + 7 bit rowindex + 7bit col_index
//`define  	CUR_Y_G_BASEADR  	8'h10
`define  	CUR_Y_GNC_BASEADR  	8'h12
`define  	CUR_Y_NCG_BASEADR 	8'h13
`define  	CUR_Y_NC_BASEADR  	8'h14

`define  	CUR_YG_IM_BASEADR   8'h15 //20 bit fxs20_12
`define 	CUR_YG_RE_BASEADR   8'h16 //20 bit fxs20_12
`define 	RECV1_RE_BASEADR	8'h17
`define 	RECV1_IM_BASEADR	8'h18
`define 	RECV2_RE_BASEADR	8'h19
`define 	RECV2_IM_BASEADR	8'h1A

`define 	RESET_Y_RECV_CONFIG	8'h1B

`define 	CURRENT_FLAG1_START_LOCMD	9'h020 //  ???// 24 bit format : {8'h00,2'b00,5'b00,CURRENT_FLAG1_START_LOCMD[8:0]}  

`define SET_GENERATOR_NUMBER	9'h127
`define SET_LOAD_NUMBER     	9'h128
`define SET_BUS_NUMBER      	9'h129
`define SET_GENBUS_ORDER    	9'h12A
`define SET_EXC_BUS_INDX	  	9'h12B // by this command we set eply address :  {exc_addr[4:0],bus_addr[6:0],GEN_Code[1:0],psi_addr[4:0],`REPORT_BUS_THETA_VALUE[8:0]}}

//bus registers :
////////////////////////////////////////////////////
`define UPDATAE_LOAD_Voltage         24'h123401
`define UPDATAE_NONLOAD_VOLTAGE      24'h123402
//define REPORT_BUS_VOLTAGE_VALUE     24'h123404
`define SET_LOADBUS_VOLTAGE_BASEADDR 24'h123480 // command from nc_Load via system controller {bus_volatage}// bus_num is in address offsert

`define GET_LINE_ILF                 24'h123402 // read dedicated busvoltage ( bus num on data bus) to shoe to user ???
`define GET_LINE_ILT                 24'h123402 // read dedicated busvoltage ( bus num on data bus) to shoe to user ???
// 
`define GET_BUS_VOLTAGE              9'h102 // read dedicated busvoltage ( bus num on data bus) to shoe to user ???
`define GET_BUS_THETA                9'h102 // read dedicated busvoltage ( bus num on data bus) to shoe to user ???
`define REPORT_BUS_VOLTAGE_VALUE   9'h102 // read dedicated busvoltage ( bus num on data bus) to shoe to user ???
`define REPORT_BUS_THETA_VALUE      9'h102 // read dedicated busvoltage ( bus num on data bus)  send to exc or show to user
`define REPORT_LINE_ILF_offset       9'h102 // read dedicated busvoltage ( bus num on data bus) show to user ???
`define REPORT_LINE_ILT_offset       9'h123402 // read dedicated busvoltage ( bus num on data bus) show to user ???

// 
`define SET_RECV1_SPARS_SIZE 24'h123480 // command from nc_Load via system controller {bus_volatage}// bus_num is in address offsert
`define SET_RECV2_SPARS_SIZE 24'h123481 // command from nc_Load via system controller {bus_volatage}// bus_num is in address offsert

/// topology specific defines 
//Generation Engin Local offset =>   addr =  {GenUnitCode[8:0], gen_indx[5:0] ,MAC_OFFSETs[7:0]}
// for test
`define 		LOG_ALL_VAR_LOCMD 	9'h084 // specific for each machin 
// new constant for exciter 
`define 	EXC_VEP_COEFFICIENT_MAG_LOCADR	9'h085
`define 	EXC_VEP_COEFFICIENT_PHASE_LOCADR	9'h086
`define 	EXC_VE_COEFFICIENT_MAG_LOCADR	9'h087
`define 	EXC_VE_COEFFICIENT_PHASE_LOCADR	9'h088

`endif // REGISTER_MAP_DEFINE_VH

