`timescale 1ns / 1ps

module tb;

   reg [7:0] sw;
   reg       clk;
   reg       btnS;
   reg       btnR;
   
   // array for instructions from seq.code. Can hold max of 8 bits
   reg [7:0] instructions [1023:0];
   integer   i;
   integer lines;
   
   /*AUTOWIRE*/
   // Beginning of automatic wires (for undeclared instantiated-module outputs)
   wire                 RsRx;                   // From model_uart0_ of model_uart.v
   wire                 RsTx;                   // From uut_ of basys3.v
   wire [7:0]           led;                    // From uut_ of basys3.v
   // End of automatics

   initial
     begin
        //$shm_open  ("dump", , ,1);
        //$shm_probe (tb, "ASTF");

        clk = 0;
        btnR = 1;
        btnS = 0;
        #1000 btnR = 0;
        #1500000;

        // Read from seq.code
        $readmemb("seq.code", instructions); 

        // get amount of instructions using first line
        lines = instructions[0];

        for (i = 1; i <= lines; i = i + 1) begin
         tskRunInst(instructions[i]);
        
      //   tskRunPUSH(0,4);s
      //   tskRunPUSH(0,0);
      //   tskRunPUSH(1,3);
      //   tskRunMULT(0,1,2);
      //   tskRunADD(2,0,3);
      //   tskRunSEND(0);
      //   tskRunSEND(1);
      //   tskRunSEND(2);
      //   tskRunSEND(3);
        
        #1000; 
        end       
        $finish;
     end

   always #5 clk = ~clk;
   
   model_uart model_uart0_ (// Outputs
                            .TX                  (RsRx),
                            // Inputs
                            .RX                  (RsTx)
                            /*AUTOINST*/);

   defparam model_uart0_.name = "UART0";
   defparam model_uart0_.baud = 1000000;
   
   
   basys3 uut_ (/*AUTOINST*/
                // Outputs
                .RsTx                   (RsTx),
                .led                    (led[7:0]),
                // Inputs
                .RsRx                   (RsRx),
                .sw                     (sw[7:0]),
                .btnS                   (btnS),
                .btnR                   (btnR),
                .clk                    (clk));

   task tskRunInst;
      input [7:0] inst;
      begin
         $display ("%d ... Running instruction %08b", $stime, inst);
         sw = inst;
         #1500000 btnS = 1;
         #3000000 btnS = 0;
      end
   endtask //

   task tskRunPUSH;
      input [1:0] ra;
      input [3:0] immd;
      reg [7:0]   inst;
      begin
         inst = {2'b00, ra[1:0], immd[3:0]};
         tskRunInst(inst);
      end
   endtask //

   task tskRunSEND;
      input [1:0] ra;
      reg [7:0]   inst;
      begin
         inst = {2'b11, ra[1:0], 4'h0};
         tskRunInst(inst);
      end
   endtask //

   task tskRunADD;
      input [1:0] ra;
      input [1:0] rb;
      input [1:0] rc;
      reg [7:0]   inst;
      begin
         inst = {2'b01, ra[1:0], rb[1:0], rc[1:0]};
         tskRunInst(inst);
      end
   endtask //

   task tskRunMULT;
      input [1:0] ra;
      input [1:0] rb;
      input [1:0] rc;
      reg [7:0]   inst;
      begin
         inst = {2'b10, ra[1:0], rb[1:0], rc[1:0]};
         tskRunInst(inst);
      end
   endtask //

   always @ (posedge clk)
     if (uut_.inst_vld)
       $display("%d ... instruction %08b executed", $stime, uut_.inst_wd);

   always @ (led)
     $display("%d ... led output changed to %08b", $stime, led);
   
endmodule // tb
// Local Variables:
// verilog-library-flags:("-y ../src/")
// End:
