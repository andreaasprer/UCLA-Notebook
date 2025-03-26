`timescale 1ns / 1ps

module get_cathode(

   //DISPLAY STATE and CATHODE
   input [3:0] display_state,
   output reg [6:0] cathode
);


   //retrive the constants
   `include "stopwatch_constants.v"


   always @* begin
       case(display_state)
           0: cathode = ZERO;
           1: cathode = ONE;
           2: cathode = TWO;
           3: cathode = THREE;
           4: cathode = FOUR;
           5: cathode = FIVE;
           6: cathode = SIX;
           7: cathode = SEVEN;
           8: cathode = EIGHT;
           9: cathode = NINE;
       endcase
   end


endmodule


