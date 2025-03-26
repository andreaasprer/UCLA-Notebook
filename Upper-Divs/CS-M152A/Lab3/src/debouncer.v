`timescale 1ns / 1ps

module debouncer(
   //INPUTS
   input clk,
   input signal_i,
   //OUTPUT
   output signal_f
);
  
    `include "stopwatch_constants.v"

   // Register to track if the signal is consistenly held
  
   reg [15:0] counter = 0;
  
   // Registers for metastability
   reg store;
   reg temp_signal;
   reg cur_signal;
  
   // Handle metastability
   always @(*) begin
       // Store input for metastability
       store <= signal_i;
   end
  
   always @(posedge clk) begin
       // Read stored input
       temp_signal <= store;
   end
  
   // Handle debouncing
   always @(posedge clk) begin
       // Check for changing signal
       if (cur_signal == temp_signal) begin
           counter <= 0;
       // If signal has changed
       end else begin
           // Count
           counter <= counter + 1'b1;
           // Once signal is constant, flip it
           if (counter == DB_COUNT) begin
               cur_signal <= temp_signal;
               counter <= 0;
           end
       end
   end
  
   // Output the current signal state
   assign signal_f = cur_signal;


endmodule