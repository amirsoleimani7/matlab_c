// like C funtion
`include "RegisterMap_Defines.vh"
// we start broadcast address from 24'hFFFFFFE0 to 24'hFFFFFFFF
// `define GenUnitCode     10'h002 //{8'h00,2'b10}
// /// 2 bit code in address definition 
// `define PS_CODE 2'b11  // all broadcast address 
// `define GEN_CODE 2'b10
// `define CUR_LOAD_CODE 2'b01
// `define CTRL_CODE 2'b00
// //////////////// Global address
// // global address and corresponding local addresses :  lower range of machin address is used for shre global and locals
// 	//////////////////
// `define 	TOPLOGY_CONF_GLBADR		24'hFFFE01// 9'h001// ps -<system controller :{generator_numbers[5:0],load_numbers[5:0],bus_num[7:0],line_num[7:0],svc_num[3:0]}
// `define 	INITIALIZE_DONE_GLBCMD	24'hFFFE02// 9'h002
// `define 	NEW_CONFIG_GLBCMD		24'hFFFE03// 9'h003
// `define 	RESET_CONFIG_GLBCMD		24'hFFFE04// 9'h004

// `define 	FLAG1_START_GLBCMD		24'hFFFE05// 9'h005
// `define 	FLAG2_START_GLBCMD		24'hFFFE06// 9'h006
// `define 	PREDICT_UPD_GLBCMD		24'hFFFE07// 9'h007
// `define 	CORRECT_UPD_GLBCMD		24'hFFFE08// 9'h008


// `define  	H_SOL_GLBADR		24'hFFFE09// 9'h009//{BROADCAST_TYPE[14:0],H_SOL_GLBADR[8:0]} 
// `define 	BASRAD_GLBADR		24'hFFFE0A// 9'h00A
// `define 	BASMVA_GLBADR		24'hFFFE0B// 9'h00B
// `define 	SYS_FREQ_GLBADR		24'hFFFE0C// 9'h00C

// `define 	BUS_CONF_THETA_BASADR			24'hFFFF01 // 9'h101//{bus_num[7:0], theta[15:0]}
// `define 	BUS_CONF_VOLTAGE_BASEADR		24'hFFFF05// 9'h105 //{bus_num[7:0],busv[15:0]}

// `define 	PM_SIG_GLBADR		24'hFFFF21// 9'h121
// `define 	EXC_SIG_GLBADR		24'hFFFF22// 9'h122
// `define 	TG_SIG_GLBADR		24'hFFFF23// 9'h123
// `define 	SVC_SIG_GLBADR		24'hFFFF24// 9'h124


// `define 	ISIM_START_Step1_GLBCMD	24'hFFFF09// 9'h109
// `define 	ISIM_START_Step2_GLBCMD	24'hFFFF0A// 9'h10A
// `define 	ISIM_START_Step3_GLBCMD	24'hFFFF0B// 9'h10B
// `define 	NCLOAD_START_GLBCMD		24'hFFFF0C // 9'h10C



// //*********NC_Load address 
// `define 	SYSTEM_LOG_CONF_GLBADR	24'h1FFF31//9'h131
// `define 	NC_LOAD_LOW_THRESHOLD	24'h1FFF32//9'h132
// `define 	NC_LOAD_VNC0			24'h1FFF33//9'h133
// `define 	NC_LOAD_VNC_BUSNUM		24'h1FFF34//9'h134





		

 		
// //`define 	H_SOL_GLBADR	24'hFFFF36= 
// //parameter  BROADCAST_TYPE  = 15'h7fff  // 24 -9 =15 bit 

// `define 	H_SOL_LOCADR	9'h009
// `define 	BASRAD_LOCADR	9'h00A
// `define 	BASMVA_LOCADR	9'h00B
// `define 	SYS_FREQ_LOCADR	9'h00C

// `define 	PM_SIG_LOCADR	9'h121
// `define 	EXC_SIG_LOCADR	9'h122
// `define 	TG_SIG_LOCADR	9'h123
// `define 	SVC_SIG_LOCADR	9'h124



// `define  RESET_CONFIG_LOCMD		9'h004
// `define  MAC_FLAG1_START_LOCMD	9'h005
// `define  MAC_FLAG2_START_LOCMD	9'h006
// `define  PREDICT_UPD_LOCMD		9'h007
// `define  CORRECT_UPD_LOCMD		9'h008

// // new define added after design phase // 4 bit command is defined for each command

// `define 		PS_GET_STAUS_GLBCMD	    24'hFFFF0D
// `define 		SYSCTRL_GET_STAUS_DATA	24'hFFFF0E

// // Y tables 8bit address 24 bit data is written in memory by pS via AXI Interface 
// // 8 bit address is read and send to system controller 

// // switch address


// `define 	GenUnit_OUT_PSI_CODE	24'hFFFE21//9'h021
// `define 	GET_ENGIN_indx_PSI		24'hFFFE22//9'h022
// `define 	ANS_ENGIN_indx_PSI		24'hFFFE23//9'h023
// `define 	ENGIN_PSI_REPORT_END	24'hFFFE24//9'h024
// `define 	CURENT_REPORT_END		24'hFFFE25//9'h025// shows end of current process ang log 
// `define 	GET_READY_STATUS		24'hFFFE26//9'h026
// `define 	SW_READY_STATUS			24'hFFFE27//9'h027
// //`define 	SET_GENERATOR_NUMBER	24'hFFFE28
// //`define 	SET_LOAD_NUMBER     	24'hFFFE29
// //`define 	SET_BUS_NUMBER      	24'hFFFE2A
// //`define 	SET_GENBUS_ORDER    	24'hFFFE2B

//  	///////////////////////////
// 	//each  generation unit adress  tables star with 9'h1xx
// // GEN_CODE 2'b10
// 	// single registers satrt with 9'h0xx
// `define  GENERATION_UNIT_CONF_LOCADR	9'h010
// `define  MAC_ANG_LOCADR	9'h012
// `define  MAC_REF_LOCADR	9'h013
// `define  MAC_CON_LOC_OFFSET	9'h120
// `define  MAC_CON_INV_LOC_OFFSET	9'h140
// `define  MAC_POT_LOC_OFFSET	9'h160
// `define  MAC_EDPRIME_LOCADR	9'h014
// `define  MAC_EQPRIME_LOCADR	9'h015
// `define  MAC_PMECH_LOCADR	9'h016
  	
// `define  EXC_CON_LOC_OFFSET	9'h180
// `define  EXC_POT_LOC_OFFSET	9'h1A0
// `define  EXC_CON_INV_LOC_OFFSET	9'h1C0

// `define  PSS_CON_LOC_OFFSET	9'h1E0
// `define  PSS_POT_LOC_OFFSET	9'h180
// `define  PSS_CON_INV_LOC_OFFSET	9'h190
// `define  PSS_PSS1_LOCADR	9'h029

// `define  V_E_EXC_GLBADDR	9'h031
// `define  I_LAST_EXC_GLBADDR	9'h032
// `define  TG_CON_LOC_OFFSET	9'h1A0
// `define  TG_CON_INV_LOC_OFFSET	9'h1B0
// `define  TG_POT_LOC_OFFSET	9'h1C0
// `define  TG1_LOCADR	9'h036
// `define  TG2_LOCADR	9'h037
// `define  TG3_LOCADR	9'h038

// `define  EXC_V_R_LOCADR	9'h040
// `define  EXC_V_AS_LOCADR	9'h041
// `define  EXC_V_RTR_LOCADR	9'h042
//  // common GLB LOC Address :




//  // 9'h01x
// `define  PSS_FLAG1_START_LOCMD	9'h014
// `define  EXC_FLAG1_START_LOCMD	9'h015
// `define  TG_FLAG1_START_LOCMD	9'h016
// //`define  MAC_FLAG2_START_LOCMD	9'h017
// `define  PSS_FLAG2_START_LOCMD	9'h018
// `define  EXC_FLAG2_START_LOCMD	9'h019
// `define  TG_FLAG2_START_LOCMD	9'h01A










// `define  MAC_ANG_SIN_LOCADR	9'h053
// `define  MAC_ANG_COS_LOCADR	9'h054
// //`define  MAC_PSI_RE_LOCADR	9'h055
// //`define  MAC_PSI_IM_LOCADR	9'h056
// `define  MAC_PSI_LOCADR	9'h057
 	
// `define  MAC_PSIKD_LOCADR	9'h060
// `define  MAC_PSIKQ_LOCADR	9'h061
// `define  MAC_SPD_LOCADR	9'h062
// `define  MAC_ETERM_LOCADR	9'h063
// `define  EXC_PELEC_LOCADR	9'h064
// `define  EXC_QELEC_LOCADR	9'h065
// `define  EXC_VEX_LOCADR	9'h066
// `define  TG_PMECH_LOCADR	9'h067
	
// `define  PSS_PSS_OUT_LOCADR	9'h070
// // current to machin controller :

// `define  BUS_V_LOCADR		9'h074
// `define  THETA_LOCADR		9'h075
// `define  CUR_RE_LOCADR		9'h076
// `define  CUR_IM_LOCADR		9'h077


// `define  EXC_REPORT_DONE	9'h082
// `define  TG_REPORT_DONE		9'h083

// // curent Address interface with system controller 
// // current data manager interface via system controller ( short code)
// //  curr_Blk_ID =0 [23:9] =0 startaddr = 24'h00000


// `define  CUR_PSI_LOCADR		9'h011 // 9
// //`define  CUR_PSI_IM_LOCADR		8'h12

// // systemcontroller _ datamanagement_current   8 bit send/receive interface
// `define 		GET_YBUS_CONFIG			9'h001 //system_controller -> DatamAnagement
// `define 		END_YBUS_CONFIG			9'h111//24'h020000 // DatamAnagement -> system_controller//// sysctrl format is used for y=this command



// //system controller and current/bus/load communicatiion 
// // these information arepassed through data manager as packed addr,data command 
// // current data manager interface via system controller ( short code)
// //address format : 8 bit contentcode + 2 bit srccode(2'b01) + 7 bit rowindex + 7bit col_index
// //`define  	CUR_Y_G_BASEADR  	8'h10
// `define  	CUR_Y_GNC_BASEADR  	8'h12
// `define  	CUR_Y_NCG_BASEADR 	8'h13
// `define  	CUR_Y_NC_BASEADR  	8'h14

// `define  	CUR_YG_IM_BASEADR   8'h15 //20 bit fxs20_12
// `define 	CUR_YG_RE_BASEADR   8'h16 //20 bit fxs20_12
// `define 	RECV1_RE_BASEADR	8'h17
// `define 	RECV1_IM_BASEADR	8'h18
// `define 	RECV2_RE_BASEADR	8'h19
// `define 	RECV2_IM_BASEADR	8'h1A

// `define 	RESET_Y_RECV_CONFIG	8'h1B

// `define 	CURRENT_FLAG1_START_LOCMD	9'h020 //  ???// 24 bit format : {8'h00,2'b00,5'b00,CURRENT_FLAG1_START_LOCMD[8:0]}  

// `define SET_GENERATOR_NUMBER	9'h127
// `define SET_LOAD_NUMBER     	9'h128
// `define SET_BUS_NUMBER      	9'h129
// `define SET_GENBUS_ORDER    	9'h12A
// `define SET_EXC_BUS_INDX	  	9'h12B // by this command we set eply address :  {exc_addr[4:0],bus_addr[6:0],GEN_Code[1:0],psi_addr[4:0],`REPORT_BUS_THETA_VALUE[8:0]}}

// //bus registers :
// ////////////////////////////////////////////////////
// `define UPDATAE_LOAD_Voltage         24'h123401
// `define UPDATAE_NONLOAD_VOLTAGE      24'h123402
// //define REPORT_BUS_VOLTAGE_VALUE     24'h123404
// `define SET_LOADBUS_VOLTAGE_BASEADDR 24'h123480 // command from nc_Load via system controller {bus_volatage}// bus_num is in address offsert

// `define GET_LINE_ILF                 24'h123402 // read dedicated busvoltage ( bus num on data bus) to shoe to user ???
// `define GET_LINE_ILT                 24'h123402 // read dedicated busvoltage ( bus num on data bus) to shoe to user ???
// // 
// `define GET_BUS_VOLTAGE              9'h102 // read dedicated busvoltage ( bus num on data bus) to shoe to user ???
// `define GET_BUS_THETA                9'h102 // read dedicated busvoltage ( bus num on data bus) to shoe to user ???
// `define REPORT_BUS_VOLTAGE_VALUE   9'h102 // read dedicated busvoltage ( bus num on data bus) to shoe to user ???
// `define REPORT_BUS_THETA_VALUE      9'h102 // read dedicated busvoltage ( bus num on data bus)  send to exc or show to user
// `define REPORT_LINE_ILF_offset       9'h102 // read dedicated busvoltage ( bus num on data bus) show to user ???
// `define REPORT_LINE_ILT_offset       9'h123402 // read dedicated busvoltage ( bus num on data bus) show to user ???

// // 
// `define SET_RECV1_SPARS_SIZE 24'h123480 // command from nc_Load via system controller {bus_volatage}// bus_num is in address offsert
// `define SET_RECV2_SPARS_SIZE 24'h123481 // command from nc_Load via system controller {bus_volatage}// bus_num is in address offsert

// /// topology specific defines 
// //Generation Engin Local offset =>   addr =  {GenUnitCode[8:0], gen_indx[5:0] ,MAC_OFFSETs[7:0]}
// // for test
// `define 		LOG_ALL_VAR_LOCMD 	9'h084 // specific for each machin 








////////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: M. yazdian 
// 
// Create Date: 03/03/2025 01:11:30 PM
// Design Name: 
// Module Name: PST_Config_Function_Flow
// Project Name:  test PST system 
// Target Devices: 
// Tool Versions: 
// Description:  PST_SDK_FLOW  feed System_simModel
//   only Clk is generated here 
// Dependencies: LOG system and checkers can be added later 
// revisin 4 : baserad, basemva added to config 
// revisin 3: test write in file : OK: considering no heder in memory file 
// Revision 2: add read  config from file 
// Revision 0.01 - File Created
// Additional Comments:
// rev2 : new size 
//////////////////////////////////////////////////////////////////////////////////
// main task in testbench
//config_generator
//config_system




module PST_SDK_FLOW // parameters is set for current simulatiion 
#(parameter recV1_size = 16,
parameter recV2_size = 10,
parameter Yg_size = 16,
parameter Ygnc_size = 8,
parameter Ybus_fifo_size = 32
)
(
  // status and global variables // bus between system Controoller and curent
         input Clk  ,
         output reg Resetn,    
         output   			      Sys_Ctrl_m_AXI_Cmd,
         output   [31:0]     Sys_Ctrl_m_AXI_Data,
         output   [23:0]     Sys_Ctrl_m_AXI_Addr,
         // interface to DAtaMAnager fifo
         output reg  [11:0] m_YbusFifo_Last_Addr,// info for data manager ( produced bu AXI_IF from command )
            
         output reg        DataManager_m_wrEn	,
         output reg [63:0] DataManager_m_wrData ,
         output reg [11:0] DataManager_m_wrAddr
);
localparam  f_20bit = 1048576.0;
localparam  f_16bit = 65536.0;
localparam  f_12bit = 4096.0;
localparam  f_8bit = 256.0;
localparam  f_7bit = 128.0;
localparam  f_6bit = 64.0;

reg          s_AXI_Cmd ;
reg   [31:0] s_AXI_Data;
reg   [23:0] s_AXI_Addr;



assign   Sys_Ctrl_m_AXI_Cmd  =s_AXI_Cmd ;
assign   Sys_Ctrl_m_AXI_Data =s_AXI_Data;
assign   Sys_Ctrl_m_AXI_Addr =s_AXI_Addr;
 // here we read file and send proper command to system aparts
         //all system process
         // 1. reset system
         // 2. read data from file and send to system controller
         // 3. read data from file and send to Dataamanagerfifo
        // 4. give accsess to fifo from datamanager

 /////////////////////////////////////////////////////
         ///     file indicators         
         integer fid_recV1;
          integer fid_recV2;
          integer fid_Yg;
          integer fid_Ygnc;
          integer fid_Psi;
//******************parameters by defines : *********************//

localparam [8:0]  PARAM_MAC_CON_LOC_OFFSET	     =`MAC_CON_LOC_OFFSET	   ;
localparam [8:0]  PARAM_MAC_CON_INV_LOC_OFFSET	 =`MAC_CON_INV_LOC_OFFSET;
localparam [8:0]  PARAM_MAC_POT_LOC_OFFSET	     =`MAC_POT_LOC_OFFSET	   ;


          

//////////
          
integer indx; 
reg  [8:0] addr;
reg [23:0] addr24;
reg [8:0] addr9;
reg [7:0] addr8;

reg [23:0] GLBaddr;
reg signed [31:0] data;

real theta;
real basemva;
real basrad;
reg [4:0] GenID;
//
real   mac_ang [0:3];//fxs_25_16//fxs16_12
real   mac_ref [0:3];//fxs_25_16//fxs16_12
real   edprime [0:3];//fxs_20_16//fxs16_12
real   eqprime [0:3];//fxs_20_16//fxs16_12
real   pmech [0:3]; //fxs_14_7 //fxs16_12
real   pelec [0 :3];//fxs_14_7
real   vex [0:3];   // fx_17_12
real   psikd[0:3];  //fxs_24_16
real   psikq[0:3];  //fxs_24_16
//real   mac_pot [1:15];//fxs16_12
//real   mac_con [1:23];//fxs16_12

reg [11:0] fifo_wrAddr;


reg [11:0] ConfMemory_size;
reg [31:0] Null;
reg [31:0] AXI_Data;
reg [23:0] AXI_Addr;

reg [7:0] ybus_code;//  8bit code to generate address 
reg signed [31:0] ymem_data;

reg [2:0] ybus_mod;// all config for bypass in separate file 
///////////////////////////////////////////////////////
          /// parameters :

localparam GenUnitCode_param =2'b10; // 2'b00 for load, 2'b01 for bus, 2'b10 for generator

///////////////////////////////////////////////////////////
          ///     Test Scenario:  main process control 
initial begin
  m_YbusFifo_Last_Addr =0;
  s_AXI_Cmd   =0;//Sys_Ctrl_m_AXI_Cmd   =0;
  s_AXI_Data  =0;//Sys_Ctrl_m_AXI_Data  =0;
  s_AXI_Addr  =0;//Sys_Ctrl_m_AXI_Addr  =0;
  AXI_Data  =0;//Ybus_m_AXI_Data  =0;
  AXI_Addr  =0;//Ybus_m_AXI_Addr  =0;
  DataManager_m_wrEn	 =0;
  DataManager_m_wrData =0;
  DataManager_m_wrAddr = 0;

end 

reg reset_done;
reg init_done;
reg config_system_done;
reg config_generator_done;
reg config_macpot_done;
reg config_maccon_done;
reg config_Ybus_done;
reg config_recV1_done;
reg config_Yg_done;

initial begin
  reset_done =0;
  init_done =0;
  config_system_done =0;
  config_generator_done =0;
  config_macpot_done =0;
  config_maccon_done =0;
  config_Ybus_done =0;
  config_recV1_done =0;
  config_Yg_done =0;


end 


initial
begin
  // call precess ://
  // 1. reset system
  reset_system();
  get_Flag0_parameters();
  repeat (35)@(posedge Clk);	
  m_YbusFifo_Last_Addr <= Ybus_fifo_size -1 ; // index of memorymust be sent
  config_system(); // config system process
  config_Generators();
  Config_Mac_pots();
  Config_Mac_cons();
  INIT_DONE();// after this command no access to machin from PS : @@Check !!!
    /////////////////////////////////////
  ybus_mod =1;
  Config_Ybus(ybus_mod);
    // SEND Y Admitance to DATA MANAGER 
  RESET_CONFIG();// force hardware to initiate from Ybus memeory
    
  repeat (100000)  @(posedge Clk); 
  ybus_mod =2;  
  Config_Ybus(ybus_mod); // check next configuration 
  // SEND Y Admitance to DATA MANAGER 
  RESET_CONFIG();// force hardware to initiate from Ybus memeory
  repeat (10000000)  @(posedge Clk); 
  //
    $stop;
  end 

  //////
task INIT_DONE();

    reg signed [31:0] data;
    begin 
      data = 0;
      //addr = {9'h1FF,6'h00,`INITIALIZE_DONE_GLBCMD};
      addr24 = `INITIALIZE_DONE_GLBCMD;
      send_PS_data(addr24 , data);
      init_done =1;
      end 
endtask

///////////
task RESET_CONFIG();
  reg signed [31:0] data;
  begin 
    repeat (5)@(posedge Clk);
      addr24 = `RESET_CONFIG_GLBCMD;
      data =0;
      send_PS_data(addr24 ,data );
      reset_done =1;
  end
endtask
////////////////////////   config system process
task config_system();
  reg [8:0] addr;
reg[23:0] addr24;
    begin
      // config_system:
      
// `define SET_GENERATOR_NUMBER	9'h127
//       `define SET_LOAD_NUMBER     	9'h128
//       `define SET_BUS_NUMBER      	9'h129
//       `define SET_GENBUS_ORDER    	9'h12A
//       `define SET_EXC_BUS_INDX	  	9'h12B 

      // set number of generators, loads and buses
      addr = `SET_GENERATOR_NUMBER;
      data = 4; // number of generators
      send_Broadcast_data(addr,data );
      addr = `SET_LOAD_NUMBER;
      data = 2; // number of loads
      send_Broadcast_data(addr,data );
      addr = `SET_BUS_NUMBER;
      data = 4; // number of buses  
      send_Broadcast_data(addr,data );
      addr = `SET_GENBUS_ORDER;
      data = 8'h00; // order of generators and buses
      send_Broadcast_data(addr,data );
      addr = `SET_EXC_BUS_INDX;
      data = 8'h00; // bus index for exciter    
      send_Broadcast_data(addr,data );


      // set system frequency
      addr24 = `SYS_FREQ_GLBADR;//fxs_10_6
      data = 50 * f_6bit; // system frequency in Hz
      send_PS_data(addr24,data );
      // set system base mva =100 : base power
      addr24 = `BASMVA_GLBADR;
      basemva = 100  ; // base power in MVA//fxs_7_0
      data = basemva;//2* 3.14 * 50 *f_7bit ;
      send_PS_data(addr24,data );

      // set basrad = 2pi*f
      addr24 = `BASRAD_GLBADR;//
      basrad =  2* 3.14 * 60 *f_8bit ; // base power in MVA//fxs_18_8
      data = basrad;//2* 3.14 * 60 *f_8bit ;
      send_PS_data(addr24,data );


      // set H_SOL: //fxs_18_16
      addr24 = `H_SOL_GLBADR;
      data =  0.01 * f_20bit; // H_SOL in per unit
      send_PS_data(addr24,data );
      // set system log configuration
      addr24 = `SYSTEM_LOG_CONF_GLBADR;
      data = 0; // no logging for now
      send_PS_data(addr24,data );
      // set NC load low threshold
      // addr = `NC_LOAD_LOW_THRESHOLD;
      // data = 0; // no low threshold for now
      // send_PS_data(addr,data );
      // // set NC load VNC0
      // addr = `NC_LOAD_VNC0;
      // data = 0; // no VNC0 for now
      // send_PS_data(addr,data );
      // // set NC load VNC bus number
      // addr = `NC_LOAD_VNC_BUSNUM;
      // data = 0; // no VNC bus number for now
      // send_PS_data(addr,data );
      // set H_SOL

      // set generation unit configuration
      addr = `GENERATION_UNIT_CONF_LOCADR	;
//config_nopss_tg_exc  machines : em/tra/sub/sub
      GenID = 0;//em
  data = {2'b01,4'b0001} ;
  send_data_to_generation(addr,data,GenID ); //em  //{MAC_MODE[1:0],EXC_EN,PSS_EN,TG_EN,GEN_EN}  // em :01 sub :10  tra 11
    GenID = 1;//tra
  data = {2'b11,4'b0001} ;
  send_data_to_generation(addr,data,GenID ); //em  //{MAC_MODE[1:0],EXC_EN,PSS_EN,TG_EN,GEN_EN}  // em :01 sub :10  tra 11
    GenID = 2;//sub
  data = {2'b10,4'b0001} ;
  send_data_to_generation(addr,data,GenID ); //em  //{MAC_MODE[1:0],EXC_EN,PSS_EN,TG_EN,GEN_EN}  // em :01 sub :10  tra 11
    GenID =3;//sub
  data = {2'b10,4'b0111} ;
  send_data_to_generation(addr,data,GenID ); //em  //{MAC_MODE[1:0],EXC_EN,PSS_EN,TG_EN,GEN_EN}  // em :01 sub :10  tra 11
  config_system_done=1;
    end

endtask






//////////////config machins 
task config_Generators();
reg [8:0] addr;

  begin
    //sys_freq = 50; */
    
    // GLBaddr = `BASMVA_GLBADR;
    // basemva =  2* 3.14 * 50 *f_7bit ;
    // data = basemva;//2* 3.14 * 50 *f_7bit ;
    // send_PS_data(GLBaddr,data );   
    
    
    // GLBaddr = `H_SOL_GLBADR;
    // data =  0.01 * f_12bit;
    // send_PS_data(GLBaddr,data );
  
  // mac_ang =[30,45,60,180];   
  for (indx = 0; indx < 4; indx = indx +1) begin
      data = mac_ang[indx] *3.14 /180 *f_16bit;
      addr = `MAC_ANG_LOCADR;
      send_data_to_generation(addr,data,indx[4:0] );
  end
  /////////
  mac_ref[0] =0;
  mac_ref[1] =0;
  mac_ref[2] =0;
  mac_ref[3] =0;
  //mac_ref =[0,0,0,0];	
  for (indx = 0; indx < 4; indx = indx +1) begin
      data = mac_ref[indx] *f_16bit;
      addr = `MAC_REF_LOCADR;
      send_data_to_generation(addr,data,indx[4:0] );
  end
    
  ///////////////////
  
  // edprime =[2,2,2,2];
  for (indx = 0; indx < 4; indx = indx +1) begin
      data = edprime[indx] *f_16bit;
      addr = `MAC_EDPRIME_LOCADR;
      send_data_to_generation(addr,data,indx[4:0] );
  end
  ////////////////	

  
  //eqprime =[3,3,3,3];
  for (indx = 0; indx < 4; indx = indx +1) begin
      data = eqprime[indx] *f_16bit;
      addr = `MAC_EQPRIME_LOCADR;
      send_data_to_generation(addr,data,indx[4:0] ); 
  end 
  /////////////////////



  //pmech
  for (indx = 0; indx < 4; indx = indx +1) begin
    data = pmech[indx] *f_7bit;//fxs_14_7
          addr = `MAC_PMECH_LOCADR;
          send_data_to_generation(addr,data,indx[4:0] ); //em  //{MAC_MODE[1:0],EXC_EN,PSS_EN,TG_EN,GEN_EN}  // em :01 sub :10  tra 11
      end 
  //pelec
    for (indx = 0; indx < 4; indx = indx +1) begin
    data = pelec[indx] *f_7bit;//fxs_14_7
          addr = `EXC_PELEC_LOCADR;
          send_data_to_generation(addr,data,indx[4:0] ); //em  //{MAC_MODE[1:0],EXC_EN,PSS_EN,TG_EN,GEN_EN}  // em :01 sub :10  tra 11
      end 
        
   //psikd 
   for (indx = 0; indx < 4; indx = indx +1) begin
    data = psikd[indx] *f_16bit;//fxs_24_16
          addr = `MAC_PSIKD_LOCADR;
          send_data_to_generation(addr,data,indx[4:0] ); //em  //{MAC_MODE[1:0],EXC_EN,PSS_EN,TG_EN,GEN_EN}  // em :01 sub :10  tra 11
      end  
//psikq 
   for (indx = 0; indx < 4; indx = indx +1) begin
    data = psikq[indx] *f_16bit;//fxs_24_16
          addr = `MAC_PSIKQ_LOCADR;
          send_data_to_generation(addr,data,indx[4:0] ); //em  //{MAC_MODE[1:0],EXC_EN,PSS_EN,TG_EN,GEN_EN}  // em :01 sub :10  tra 11
      end 
// vex 
    for (indx = 0; indx < 4; indx = indx +1) begin
    data = vex[indx] *f_12bit;//fxs_17_12
          addr = `MAC_PSIKQ_LOCADR;
          send_data_to_generation(addr,data,indx[4:0] ); //em  //{MAC_MODE[1:0],EXC_EN,PSS_EN,TG_EN,GEN_EN}  // em :01 sub :10  tra 11
      end   

//pss1

      //tg1,tg2,tg3



    config_generator_done =1; 
  end
    

endtask
/////////////////////////// macpot , mac_con : simple version :

reg [2048:0] head;

 integer mac_pot_fid;

task Config_Mac_pots();
       
    integer  i ,j,r;
    reg [8:0] baseaddr,baseaddr_Inv;
    reg [8:0] addr9;

    reg signed [31:0] mac_pot_fixdpoint ;
    reg signed [31:0] mac_pot_Inv_fixdpoint ;
reg [4:0] mac_num;
reg [4:0]  mac_pot_indx;
begin 
  mac_pot_fid =  $fopen("Rep_mac_pot.mem", "r");
  if (mac_pot_fid == 0) begin
    $display("Failed to open 'Rep_mac_pot.mem'  file");
    $finish;
  end
  else begin

     baseaddr = `MAC_POT_LOC_OFFSET ;
    //baseaddr_inv = `MAC_POT_INV_LOC_OFFSET ;

// Skip header
     //r = $fgets(head,mac_pot_fid);  // discard the first line

      for(i=0; i< 4; i=i+1) begin
        for(j=0; j< 15; j=j+1) begin
          r = $fscanf(mac_pot_fid, "%d,%d,%d,%d\n",mac_num, mac_pot_indx , mac_pot_fixdpoint  ,mac_pot_Inv_fixdpoint);
        $display("mac_pot   :::%d , %d ,%d   " , mac_num, mac_pot_indx,mac_pot_fixdpoint);
          //mac_pot_scaled = mac_pot_val * f_12bit;
        
          
          // set one mac_pot item:
          addr9 = {baseaddr[8:5],mac_pot_indx[4:0]};     
          send_data_to_generation(addr9 , mac_pot_fixdpoint , mac_num );

          
         
      end
    end 
    config_macpot_done=1;
    $fclose(mac_pot_fid);

    end 
  end
     




endtask

 integer mac_con_fid;

task Config_Mac_cons();
       
    integer  i ,j,r;
    reg [8:0] baseaddr,baseaddr_Inv;
    reg [8:0] addr9;

    reg signed [31:0] mac_con_fixdpoint ;
    reg signed [31:0] mac_con_Inv_fixdpoint ;

reg [4:0] mac_num;
reg [4:0]  mac_con_indx;
real mac_con_val;
real   mac_con_scaled;
real mac_con_Inv_scaled;
reg signed [31:0]  tmp_im;
begin 
  mac_con_fid =  $fopen("Rep_mac_con.mem", "r");
  if (mac_con_fid == 0) begin
    $display("Failed to open 'Rep_mac_con.mem'  file");
    $finish;
  end
  else begin

     baseaddr = `MAC_CON_LOC_OFFSET ;
     baseaddr_Inv = `MAC_CON_INV_LOC_OFFSET;
// Skip header
     //r = $fgets(head,mac_con_fid);  // discard the first line

      for(i=0; i< 4; i=i+1) begin
        for(j=0; j< 23; j=j+1) begin
          r = $fscanf(mac_con_fid, "%d,%d,%d,%d\n",mac_num, mac_con_indx,mac_con_fixdpoint,tmp_im);// only real part is used.. scale value are saved in 
          $display("mac_con  : %d,%d,%d " ,mac_num, mac_con_indx,mac_con_fixdpoint);
          
          // set one mac_con item:
          addr9 = {baseaddr[8:5],mac_con_indx[4:0]};     
          send_data_to_generation(addr9 , mac_con_fixdpoint , mac_num );
          // set one mac_con_Inv item :
          mac_con_scaled = mac_con_fixdpoint;
          if (mac_con_scaled != 0) begin 
            mac_con_Inv_scaled = (1/mac_con_scaled) * f_12bit * f_12bit;//
            mac_con_Inv_fixdpoint= mac_con_Inv_scaled;

            addr9 = {baseaddr_Inv[8:5],mac_con_indx[4:0]};     
            send_data_to_generation(addr9 , mac_con_Inv_fixdpoint , mac_num );
          end 
      end
    end 
    config_maccon_done=1;
    $fclose(mac_con_fid);

    end 
  end
     



endtask





  ////////////////////////////////////////////////////////

task  Config_Ybus;
input [2:0] ybus_configmod;

  begin
    fifo_wrAddr  = 0;
    // read Yg data from file and send to system controller 
    
     send_Yg_data(ybus_configmod);
    
    // read Ygnc data from file and send to system controller 
    // send_Ygnc_data();
    // recV1 data from file and send to system controller 
     send_recV1_data(ybus_configmod); // sparcematrix
     send_ybus_size(fifo_wrAddr); // end data index is use as size:
     // this proces is implemented in s00_axi_PSIF.v by writing in slvreg3 module reach end of process 
     config_Ybus_done =1;
  end   
endtask
///////////////////
    task send_ybus_size;
    input [11:0]  Ybus_size ;
begin
  m_YbusFifo_Last_Addr   <=   Ybus_size;//Ybus_fifo_size;// Ybus_size;//Ybus_fifo_size

end 

endtask



task send_recV1_data;
input [2:0] Ybus_mod;
           integer fd,cnt,recV1_fid;
      integer r;
      reg  [6:0] row,col;
      reg signed [19:0] recV1_real,recV1_imag;
      begin

        case (Ybus_mod)

        1: recV1_fid = $fopen("Rep_rec_V1_mode1.mem", "r");
        2: recV1_fid = $fopen("Rep_rec_V1_mode2.mem", "r");
        3: recV1_fid = $fopen("Rep_rec_V1_mode3.mem", "r");
        default : begin
           $display("// incorrect Ybus_mod : Failed to open 'Rep_rec_V1'  file// ");
          $finish;
        end 
        endcase 

      
            
        if (recV1_fid == 0) begin
          $display("Failed to open 'Rep_rec_V1'  file");
          $finish;
        end 
             cnt =0;

       //while (!$feof(fd))
         while (cnt < recV1_size)
        begin
          r = $fscanf(recV1_fid, "%d,%d,%d,%d\n", row, col, recV1_real,recV1_imag);
           $display("recV1_fid hex  :::::, %d,%d,%h,%h", row, col, recV1_real,recV1_imag);
                        
         
          // send dat from datamanager to current via systemController 
          addr8=`RECV1_RE_BASEADR;
          send_DataManager_Model_data(addr8,row,col, recV1_real); 
          addr8=`RECV1_IM_BASEADR;
          send_DataManager_Model_data(addr8,row,col, recV1_imag);     
            cnt =cnt+1;
        end
        $fclose(recV1_fid);
        // send sparce matrix size :
        addr24=`SET_RECV1_SPARS_SIZE;// thisconfig is saved in datamemory but with PS format
       // send_PS_data(addr,cnt);// send size of sparce matrix to system controller  to bus_voltage
        save_PS_command_in_Datamemory(addr24,recV1_size);// send size of sparce matrix to system controller  to bus_voltage
          config_recV1_done =1;
  end 
endtask


task send_Yg_data;// Yg is complete matrix 
input [2:0] Ybus_mod;

      integer Yg_fid;
      integer cnt;
      integer r;
     
      reg signed [19:0] Yg_real;
      reg signed [19:0] Yg_imag;

      reg  [6:0] row;
      reg  [6:0] col;

      begin
         case (Ybus_mod)

        1:  Yg_fid = $fopen("Rep_Y_g_mode1.mem", "r");
        2:  Yg_fid = $fopen("Rep_Y_g_mode2.mem", "r");
        3:  Yg_fid = $fopen("Rep_Y_g_mode3.mem", "r");
        default : begin
           $display("// incorrect Ybus_mod : Failed to open 'Rep_Y_g'  file// ");
          $finish;
        end 
        endcase 


        // Yg_fid = $fopen("Rep_Y_g.mem", "r");
        if (Yg_fid == 0) begin
          $display("Failed to open 'Rep_Y_g'  file");
          $finish;
        end
        cnt =0;
        
        //while (!$feof(fd)) begin
        while (cnt < Yg_size) begin 

          r = $fscanf(Yg_fid, "%d,%d,%d,%d\n", row, col, Yg_real,Yg_imag);
          $display("Yg_fid  ::: %d,%d,%d,%d", row, col, Yg_real,Yg_imag);
         
         
     
          // send dat from datamanager to current via systemController 
          cnt =cnt+1;
          ybus_code=`CUR_YG_RE_BASEADR;
          ymem_data =Yg_real;
          send_DataManager_Model_data(ybus_code,row,col, ymem_data); 
          ybus_code=`CUR_YG_IM_BASEADR;
          ymem_data=Yg_imag;

          send_DataManager_Model_data(ybus_code,row,col, ymem_data);     

        end

        addr24=`SET_RECV1_SPARS_SIZE;
        // send_PS_data(addr,cnt);// send size of sparce matrix to system controller  to bus_voltage
        save_PS_command_in_Datamemory(addr24,Yg_size);// send size of sparce matrix to system controller  to bus_voltage


        config_Yg_done =1;

        $fclose(Yg_fid);
  end
endtask   


  ////////////////////////////////////////////




/////////////////////////////////// Basic functions :
task reset_system();
  begin
    // reset system
    Resetn <= 0;
    repeat(100)       @(posedge Clk);
    
    Resetn <= 1;
    repeat(10)       @(posedge Clk);
    
  end
endtask 

// base task for global configuration of system controller (AXI port1 -type 2'b11  modeling)
task send_PS_data;
    input [23:0]  Addr;
    input [31:0] data;
    begin
		s_AXI_Cmd	 <= 1;
		s_AXI_Data   <= {data[31:0]};
		s_AXI_Addr   <= Addr[23:0]; // {6'h71,addr[8:0]}// broadcast data
  
	@(posedge Clk);
		s_AXI_Cmd	 <= 0;
		s_AXI_Data   <= 0;
		s_AXI_Addr   <= 0;
     @(posedge Clk);
    end
endtask

task send_Broadcast_data;
    input [8:0]  Addr;
    input [31:0] data;
    begin
		s_AXI_Cmd	 <= 1;
		s_AXI_Data   <= {data[31:0]};
		s_AXI_Addr   <= {15'h7FFF,Addr[8:0]}; // {6'h71,addr[8:0]}// broadcast data
  
	@(posedge Clk);
		s_AXI_Cmd	 <= 0;
		s_AXI_Data   <= 0;
		s_AXI_Addr   <= 0;
     @(posedge Clk);
    end
endtask
// base task for sending data to  generators via system controller(AXI port1 type 2'b10 modeling)
task send_data_to_generation;
    input [8:0]  Addr;
    input [31:0] data;
    input [4:0] GenID;
    begin
		s_AXI_Cmd	 <= 1;
		s_AXI_Data   <= {data[31:0]};
		s_AXI_Addr   <={8'h00,2'b10,GenID[4:0], Addr[8:0]}; // {6'h71,addr[8:0]}
  
	@(posedge Clk);
		s_AXI_Cmd	 <= 0;
		s_AXI_Data   <= 0;
		s_AXI_Addr   <= 0;
     @(posedge Clk);
    end
endtask


// base task for sending data to datamanager (AXI port2  type 2'b01 modeling)
task send_DataManager_Model_data_cmd;//not used
//here we are modeling data manager fifo 
//after each RdEn we send next data strored  in datamanager fifo
    input [7:0]  Addr;// ybus data type 7 bit 

    input [6:0] row;
    input [6:0] col;
    input [31:0] data;
// write_slvreg0({Addr[8:0],2'b01,row[6:0],col[6:0]});
// write_slvreg1(data[31:0]);
// write_slvreg1(Null[31:0]);
// write_slvreg3(ConfMemory_size[11:0]);//show end of table + size of memory :  report in hardware vis 
    // data mustbe written in fifo 
    begin
      AXI_Data  = {data[31:0]};
      // formatting address: this process is done in driver 
      AXI_Addr   ={Addr[7:0],2'b01,row[6:0],col[6:0]}; // table cod[23:16],2'b01,row(7bit),col(7bit)
      // DataManager_m_AXI_Cmd	   <= 1;// rdVal
      // DataManager_m_AXI_Data   <= {8'h00,AXI_Addr[23:0] , AXI_Data[31:0]};//rd_data
      // DataManager_m_AXI_Addr   <= DataManager_s_AXI_Addr +1
      // // this data format must be produced in PS  and send to datamanager cancatenated Addr,data ... regenerated in Dataamanager separating command and address 
      // @(posedge Clk);
      // DataManager_m_AXI_Cmd	 <= 0;
      // DataManager_m_AXI_Data   <= 0;
      // DataManager_m_AXI_Addr   <= 0;
      // @(posedge Clk);
    end   
endtask

//
task save_PS_command_in_Datamemory;
    input [23:0]  Addr;
    input [31:0] Data;
    begin
      DataManager_m_wrEn	   <= 1;// rdVal
      DataManager_m_wrData   <= {8'h00,Addr[23:0] , AXI_Data[31:0]};//rd_data
      DataManager_m_wrAddr   <=  fifo_wrAddr;

      // this data format must be produced in PS  and send to datamanager cancatenated Addr,data ... regenerated in Dataamanager separating command and address 
      @(posedge Clk);
      DataManager_m_wrEn	   <=0;
      DataManager_m_wrData   <=0;
      fifo_wrAddr <=fifo_wrAddr+1;
      @(posedge Clk);
    
    end
endtask
//task write_DataMemory_AXIPSIF_Model();
task send_DataManager_Model_data;// main function based on  writ to fifo
    input [7:0]  Addr;// data tyope 8 bit 
    input [6:0] row;
    input [6:0] col;
    input [31:0] data;
    
    begin      
        AXI_Data  = {data[31:0]};
        // formatting address: this process is done in driver 
        AXI_Addr   ={Addr[7:0],2'b01,row[6:0],col[6:0]}; // table cod[23:16],2'b01,row(7bit),col(7bit)
       // $display("send_DataManager_Model_data: AXIAddr = %h,code = %h row = %d, col = %d, AXIdata = %h\n", AXI_Addr,Addr, row, col, AXI_Data);
        DataManager_m_wrEn	   <= 1;// rdVal
        DataManager_m_wrData   <= {8'h00,AXI_Addr[23:0] , AXI_Data[31:0]};//rd_data
        DataManager_m_wrAddr   <=  fifo_wrAddr;

        // this data format must be produced in PS  and send to datamanager cancatenated Addr,data ... regenerated in Dataamanager separating command and address 
        @(posedge Clk);
        DataManager_m_wrEn	   <=0;
        DataManager_m_wrData   <=0;
        fifo_wrAddr <=fifo_wrAddr+1;
        @(posedge Clk);

      end   
endtask

/*************************Flag0 process  **************************************/
task get_Flag0_parameters();
begin
 // I will replace these lines from file : REP/Rep_lag0_variables.vh    produced by matlab_function : save_Flag0_mac_variables.m 
//mac_ang 
mac_ang[0] = 1.22477907689511;
mac_ang[1] = 1.04166337574829;
mac_ang[2] = 0.776134158653301;
mac_ang[3] = 0.589469221098553;

//Edprime 
edprime[0] =0.583368577259401;
edprime[1] =-0.463500043137608;
edprime[2] =-0.489239957087147;
edprime[3] =0.578493784105116;


//Eqprime 
eqprime[0] =0.947954425760695;
eqprime[1] =0.954515038445469;
eqprime[2] =0.938013243017739;
eqprime[3] =0.932693011478760;



//Psikd
psikd[0] =0;
psikd[1] =0.884565836171458;
psikd[2] =0.870708615476467;
psikd[3] =0;



//Psikq
psikq[0] =0;
psikq[1] =-0.604565273657749;
psikq[2] =-0.638139074461496;
psikq[3] =0;


//vex
vex[0] =1.95018720943172;
vex[1] =2.02030586746911;
vex[2] =1.95829326933307;
vex[3] =1.96325865240304;



// Pmech
pmech[0] =0.779296724485283 ;         
pmech[1] =0.779407110691485;
pmech[2] =0.799919253932162;
pmech[3] =0.779364106286355;

//Pelec
pelec[0] =7.0000;
pelec[1] = 7.0000;
pelec[2] = 7.1850;
pelec[3] = 7.0000;



end 



endtask

endmodule
