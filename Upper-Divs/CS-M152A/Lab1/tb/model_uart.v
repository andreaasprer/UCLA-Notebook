`timescale 1ns / 1ps

module model_uart(/*AUTOARG*/
   // Outputs
   TX,
   // Inputs
   RX
   );

   output TX;
   input  RX;

   parameter baud    = 115200;
   parameter bittime = 1000000000/baud;
   parameter name    = "UART0";
   
   reg [7:0] rxData;
   reg [31:0] nicerUART;
   event     evBit;
   event     evByte;
   event     evTxBit;
   event     evTxByte;
   reg       TX;

   initial
     begin
        TX = 1'b1;
     end
   
   always @ (negedge RX) begin
      #(0.5*bittime);
      repeat (8) begin
         #bittime ->evBit;
         rxData[7:0] = {RX,rxData[7:1]};
      end
      ->evByte;

      if (rxData == 10 || rxData == 13) begin
         if (nicerUART != "")
         begin
            $display ("%d %s Received %02x (%s)", $stime, name, nicerUART, nicerUART);
         end
         nicerUART = "";
      end
      else begin
         nicerUART = {nicerUART, rxData};
      end
   end

   task tskRxData;
      output [7:0] data;
      begin
         @(evByte);
         data = rxData;
      end
   endtask // for
      
   task tskTxData;
      input [7:0] data;
      reg [9:0]   tmp;
      integer     i;
      begin
         tmp = {1'b1, data[7:0], 1'b0};
         for (i=0;i<10;i=i+1)
           begin
              TX = tmp[i];
              #bittime;
              ->evTxBit;
           end
         ->evTxByte;
      end
   endtask // tskTxData
   
endmodule // model_uart
