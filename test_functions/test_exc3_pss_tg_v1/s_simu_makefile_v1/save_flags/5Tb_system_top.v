`timescale 1ns / 1ps
//`include "RegisterMap_Defines.v"
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/03/2025 01:11:30 PM
// Design Name: 
// Module Name: TB_SYSTEM ( flow + system_simModel)
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description:  PST_SDK_FLOW  feed System_simModel
//   only Clk is generated here 
// Dependencies: LOG system and checkers can be added later 
// 
// Revision2 : add log file 
// Revision 0.01 - File Created
// Additional Comments:
// rev2: new size + file based config 
//////////////////////////////////////////////////////////////////////////////////


module TB_SYSTEM();

 reg Clk;
 wire Resetn;
 reg [31:0]  tb_counter;    

// wire 			m_AXI_Cmd;            
// wire  [31:0]    m_AXI_Data; 
// wire [23:0]     m_AXI_Addr; 

wire 			s_AXI_Cmd;            
wire  [31:0]    s_AXI_Data; 
wire [23:0]     s_AXI_Addr;  


wire [11:0] m_YbusFifo_Last_Addr;
wire [63:0] DataManager_m_wrData;
wire [11:0] DataManager_m_wrAddr;
wire        DataManager_m_wrEn;       



parameter PERIOD = 10;


   
localparam  f_20bit = 1048576.0;
localparam  f_16bit = 65536.0;
localparam  f_12bit = 4096.0;
localparam  f_7bit = 128.0;
localparam  f_8bit = 256.0;

integer file;

// main test bench
initial begin
      Clk = 1'b0;
      #(PERIOD/2);
      forever
         #(PERIOD/2) Clk = ~Clk;
   end

initial begin
        tb_counter =0;
        forever begin
                @(posedge Clk);
                tb_counter = tb_counter+1;
        end

end 



initial begin  // stimuluse generation : 
	
	
 file = $fopen("log_Tb_PSTtop.txt", "w");
        if (file == 0) begin
            $display("Error: Could not open file.");
            $finish;
        end

        // Write the values to the file
        		
		
repeat (500000)  @(posedge Clk); 
	
    
//
	$stop;
end 

// always @(   ... ) begin
// 	LOG_SystemVariables();

// end 

///    log to  files://///////



///////////////////  file :






PST_SDK_FLOW PST_SDK_FLOW_Ins(
  // status and global variables // bus between system Controoller and curent
        .Clk (Clk),
        .Resetn(Resetn) ,    
        .Sys_Ctrl_m_AXI_Cmd (s_AXI_Cmd),
        .Sys_Ctrl_m_AXI_Data(s_AXI_Data),
        .Sys_Ctrl_m_AXI_Addr(s_AXI_Addr),
        
        .m_YbusFifo_Last_Addr     (m_YbusFifo_Last_Addr),
        .DataManager_m_wrData        (DataManager_m_wrData),
        .DataManager_m_wrEn          (DataManager_m_wrEn),
        .DataManager_m_wrAddr       (DataManager_m_wrAddr)

);

///////////////////////////////
System_simModel System_simModel_ins    (
    .Clk (Clk),
   .Resetn(Resetn),
   // system controller from  PS
    .system_controller_s_AXI_Addr   (s_AXI_Addr),
    .system_controller_s_AXI_Cmd    (s_AXI_Cmd),
    .system_controller_s_AXI_Data   (s_AXI_Data),
    //SYSCTRL  to PS Interface 
    // .system_controller_m_AXI_Addr       (m_AXI_Addr),
    // .system_controller_m_AXI_Cmd       (m_AXI_Cmd),
    // .system_controller_m_AXI_Data       (m_AXI_Data),
    // data manager interface with PS( modeling duslport memory info)
    .m_YbusFifo_Last_Addr     (m_YbusFifo_Last_Addr),
    .DataManager_m_wrData        (DataManager_m_wrData),
    .DataManager_m_wrEn          (DataManager_m_wrEn),
    .DataManager_m_wrAddr       (DataManager_m_wrAddr)
    );
///////////////////////
//copy log file here:
    wire [31:0] mac0_log_data;
    wire [31:0] mac1_log_data;
    wire [31:0] mac2_log_data;
    wire [31:0] mac3_log_data;
    
    wire mac0_log_cmd;
    wire mac1_log_cmd;
    wire mac2_log_cmd;
    wire mac3_log_cmd;
    
    ///////////////////files:
    //**********************************log mac0 : 

    //mac0:
    integer fid_mac0_hex;
    integer fid_mac0_float;
    initial begin 
    fid_mac0_hex = $fopen("LOG_mac0_hex.csv", "w"); 
    fid_mac0_float = $fopen("LOG_mac0_float.csv", "w"); 
    
        
   // $fwrite(fid_mac0_hex, "		**** LOG all variables of Machin Model \n")	;	
    $fwrite(fid_mac0_hex, "	psi_re,psi_im,psiqpp,psidpp,cur_re,cur_im,curd,curq,curdg,curqg,ed,eq,eterm,pelect,qelect,mac_ang,sin_mac_ang,cos_mac_ang,edprime,eqprime,mac_spd,dmac_spd,dmac_ang,dedprime,deqprime,dpsikd,dpsikq\n")	;	
    
   // $fwrite(fid_mac0_float, "		**** LOG all variables of Machin Model \n")	;	
    $fwrite(fid_mac0_float, "	psi_re,psi_im,psiqpp,psidpp,cur_re,cur_im,curd,curq,curdg,curqg,ed,eq,eterm,pelect,qelect,mac_ang,sin_mac_ang,cos_mac_ang,edprime,eqprime,mac_spd,dmac_spd,dmac_ang,dedprime,deqprime,dpsikd,dpsikq\n")	;	
    
    repeat (500000)@(posedge Clk);	 	
            // ???? ????  
            
            $fclose(fid_mac0_hex);
            $fclose(fid_mac0_float);
    end 
    
    
    /////////////////////////
    
    assign mac0_log_cmd = System_simModel_ins.Generation_Unit_Ins0.m_Log_Cmd;
    assign mac0_log_data =System_simModel_ins.Generation_Unit_Ins0.m_Log_Data;
    
    always @(posedge  mac0_log_cmd) begin 
             log_mac0_function();
    end 
    
    
    task log_mac0_function();
        real log_float_decimal;
        real log_scaled_back_float_decimal;
        reg signed [31:0] log_fixpoint_hex;
    
    
    
        begin
            while (mac0_log_cmd ==1) begin
                log_fixpoint_hex = mac0_log_data;
                log_float_decimal = log_fixpoint_hex;
    
                log_scaled_back_float_decimal = mac0_log_data/4096.0/16.0; //  considering 16 bit fraction 
                $fwrite (fid_mac0_hex , " %h , ",log_fixpoint_hex);
                $fwrite (fid_mac0_float ," %f , ",log_scaled_back_float_decimal  );
    
                @(posedge Clk);
            end 
            $fwrite (fid_mac0_hex , "\n");
            $fwrite (fid_mac0_float ,"\n" );
    
        end 
    
            
    endtask

//**********************************log mac1 : 
//mac1:
    integer fid_mac1_hex;
    integer fid_mac1_float;
    initial begin 
    fid_mac1_hex = $fopen("LOG_mac1_hex.csv", "w"); 
    fid_mac1_float = $fopen("LOG_mac1_float.csv", "w"); 
    
        
    $fwrite(fid_mac1_hex, "		**** LOG all variables of Machin Model \n")	;	
    $fwrite(fid_mac1_hex, "	psi_re,psi_im,psiqpp,psidpp,cur_re,cur_im,curd,curq,curdg,curqg,ed,eq,eterm,pelect,qelect,mac_ang,sin_mac_ang,cos_mac_ang,edprime,eqprime,mac_spd,dmac_spd,dmac_ang,dedprime,deqprime,dpsikd,dpsikq \n")	;	
    
    $fwrite(fid_mac1_float, "		**** LOG all variables of Machin Model \n")	;	
    $fwrite(fid_mac1_float, "	psi_re,psi_im,psiqpp,psidpp,cur_re,cur_im,curd,curq,curdg,curqg,ed,eq,eterm,pelect,qelect,mac_ang,sin_mac_ang,cos_mac_ang,edprime,eqprime,mac_spd,dmac_spd,dmac_ang,dedprime,deqprime,dpsikd,dpsikq \n")	;	
    
    repeat (500000)@(posedge Clk);	 	
            // ???? ????  
            
            $fclose(fid_mac1_hex);
            $fclose(fid_mac1_float);
    end 
    
    
    /////////////////////////
    
    assign mac1_log_cmd = System_simModel_ins.Generation_Unit_Ins1.m_Log_Cmd;
    assign mac1_log_data =System_simModel_ins.Generation_Unit_Ins1.m_Log_Data;
    
    always @(posedge  mac1_log_cmd) begin 
             log_mac1_function();
    end 
    
    
    task log_mac1_function();
        real log_float_decimal;
        real log_scaled_back_float_decimal;
        reg signed [31:0] log_fixpoint_hex;
    
    
    
        begin
            while (mac1_log_cmd ==1) begin
                log_fixpoint_hex = mac1_log_data;
                log_float_decimal = log_fixpoint_hex;
    
                log_scaled_back_float_decimal = mac1_log_data/4096.0/16.0;// considering 16 bit fraction 
                $fwrite (fid_mac1_hex , " %h , ",log_fixpoint_hex);
                $fwrite (fid_mac1_float ," %.6f , ",log_scaled_back_float_decimal  );
    
                @(posedge Clk);
            end 
            $fwrite (fid_mac1_hex , " \n ");
            $fwrite (fid_mac1_float ,"\n " );
    
        end 
    
            
    endtask   

//**********************************log mac2 : 
//mac2:
    integer fid_mac2_hex;
    integer fid_mac2_float;
    initial begin 
    fid_mac2_hex = $fopen("LOG_mac2_hex.csv", "w"); 
    fid_mac2_float = $fopen("LOG_mac2_float.csv", "w"); 
    
        
    $fwrite(fid_mac2_hex, "		**** LOG all variables of Machin Model \n")	;	
    $fwrite(fid_mac2_hex, "	psi_re,psi_im,psiqpp,psidpp,cur_re,cur_im,curd,curq,curdg,curqg,ed,eq,eterm,pelect,qelect,mac_ang,sin_mac_ang,cos_mac_ang,edprime,eqprime,mac_spd,dmac_spd,dmac_ang,dedprime,deqprime,dpsikd,dpsikq \n")	;	
    
    $fwrite(fid_mac2_float, "		**** LOG all variables of Machin Model \n")	;	
    $fwrite(fid_mac2_float, "	psi_re,psi_im,psiqpp,psidpp,cur_re,cur_im,curd,curq,curdg,curqg,ed,eq,eterm,pelect,qelect,mac_ang,sin_mac_ang,cos_mac_ang,edprime,eqprime,mac_spd,dmac_spd,dmac_ang,dedprime,deqprime,dpsikd,dpsikq \n")	;	
    
    repeat (500000)@(posedge Clk);	 	
            // ???? ????  
            
            $fclose(fid_mac2_hex);
            $fclose(fid_mac2_float);
    end 
    
    
    /////////////////////////
    
    assign mac2_log_cmd = System_simModel_ins.Generation_Unit_Ins2.m_Log_Cmd;
    assign mac2_log_data =System_simModel_ins.Generation_Unit_Ins2.m_Log_Data;
    
    always @(posedge  mac2_log_cmd) begin 
             log_mac2_function();
    end 
    
    
    task log_mac2_function();
        real log_float_decimal;
        real log_scaled_back_float_decimal;
        reg signed [31:0] log_fixpoint_hex;
    
    
    
        begin
            while (mac2_log_cmd ==1) begin
                log_fixpoint_hex = mac2_log_data;
                log_float_decimal = log_fixpoint_hex;
    
                log_scaled_back_float_decimal = mac2_log_data/4096.0/16.0;// considering 16 bit fraction 
                $fwrite (fid_mac2_hex , " %h , ",log_fixpoint_hex);
                $fwrite (fid_mac2_float ," %.6f , ",log_scaled_back_float_decimal  );
    
                @(posedge Clk);
            end 
            $fwrite (fid_mac2_hex , " \n ");
            $fwrite (fid_mac2_float ,"\n " );
    
        end 
    
            
    endtask   

//**********************************log mac3 : 
//mac3:
    integer fid_mac3_hex;
    integer fid_mac3_float;
    initial begin 
    fid_mac3_hex = $fopen("LOG_mac3_hex.csv", "w"); 
    fid_mac3_float = $fopen("LOG_mac3_float.csv", "w"); 
    
        
    $fwrite(fid_mac3_hex, "		**** LOG all variables of Machin Model \n")	;	
    $fwrite(fid_mac3_hex, "	psi_re,psi_im,psiqpp,psidpp,cur_re,cur_im,curd,curq,curdg,curqg,ed,eq,eterm,pelect,qelect,mac_ang,sin_mac_ang,cos_mac_ang,edprime,eqprime,mac_spd,dmac_spd,dmac_ang,dedprime,deqprime,dpsikd,dpsikq \n")	;	
    
    $fwrite(fid_mac3_float, "		**** LOG all variables of Machin Model \n")	;	
    $fwrite(fid_mac3_float, "	psi_re,psi_im,psiqpp,psidpp,cur_re,cur_im,curd,curq,curdg,curqg,ed,eq,eterm,pelect,qelect,mac_ang,sin_mac_ang,cos_mac_ang,edprime,eqprime,mac_spd,dmac_spd,dmac_ang,dedprime,deqprime,dpsikd,dpsikq \n")	;	
    
    repeat (500000)@(posedge Clk);	 	
            // ???? ????  
            
            $fclose(fid_mac3_hex);
            $fclose(fid_mac3_float);
    end 
    
    
    /////////////////////////
    
    assign mac3_log_cmd = System_simModel_ins.Generation_Unit_Ins1.m_Log_Cmd;
    assign mac3_log_data =System_simModel_ins.Generation_Unit_Ins1.m_Log_Data;
    
    always @(posedge  mac3_log_cmd) begin 
             log_mac3_function();
    end 
    
    
    task log_mac3_function();
        real log_float_decimal;
        real log_scaled_back_float_decimal;
        reg signed [31:0] log_fixpoint_hex;
    
    
    
        begin
            while (mac3_log_cmd ==1) begin
                log_fixpoint_hex = mac3_log_data;
                log_float_decimal = log_fixpoint_hex;
    
                log_scaled_back_float_decimal = mac3_log_data/4096.0/16.0;// considering 16 bit fraction 
                $fwrite (fid_mac3_hex , " %h , ",log_fixpoint_hex);
                $fwrite (fid_mac3_float ," %.6f , ",log_scaled_back_float_decimal  );
    
                @(posedge Clk);
            end 
            $fwrite (fid_mac3_hex , " \n ");
            $fwrite (fid_mac3_float ,"\n " );
    
        end 
    
            
    endtask   





 //***********************************Save all simulation config for board test : **************   
 integer    fid_SysConf;
 integer    fid_DataManager; 
initial begin
    fid_SysConf =$fopen("Config_file_SysCtrl.txt","w");
    fid_DataManager =$fopen("Config_file_DatManager.txt","w");
 repeat(5000000)  @(posedge Clk);
    $fclose(fid_SysConf);
    $fclose(fid_DataManager);


end  

 //task Save_Log_Config();   
initial begin //: Save_Log_Config
    @(posedge Clk);
    while (1) begin 
        if (s_AXI_Cmd==1 ) begin
            $fwrite (fid_SysConf , "0x%h,0x%h \n",s_AXI_Addr,s_AXI_Data); 
        end          
            @(posedge Clk);
    end 
  
end 



//task Save_Log_YbusConfig();   
initial begin //: Save_Log_YbusConfig
    @(posedge Clk);
    while (1) begin 
        if (DataManager_m_wrEn==1 ) begin
            $fwrite (fid_DataManager , "0x%h,0x%h \n",DataManager_m_wrData[63:32],DataManager_m_wrData[31:0]); 
        end          
            @(posedge Clk);
    end 
    
end 


    
endmodule

