`timescale 1ns / 1ps

module fpcvt(D, S, E, F);

	// Inputs
	input [11:0] D;

	// Outputs
	output S;
	output [2:0] E;
	output [3:0] F;

	// Wires
	wire [11:0] signed_mag;
	wire fifth_bit;
	wire [2:0] exp;
	wire [3:0] sig;

	to_signed_magnitude m1 (.D(D), .S(S), .signed_mag(signed_mag));
	leading_zeroes m2 (.D(signed_mag), .E(exp), .F(sig), .fifth_bit(fifth_bit));
	rounding m3 (.E_in(exp), .F_in(sig), .fifth_bit(fifth_bit), .E_out(E), .F_out(F));
endmodule

module to_signed_magnitude(D, S, signed_mag);

	 // Inputs
    input [11:0] D;

    // Outputs
    output reg S;
    output reg [11:0] signed_mag;

    always @* begin
        // Extract sign bit (MSB)
        S = D[11];
        // Negative value
        if (S == 1) begin
            signed_mag = -D;

            // edge case: TMin
            if (D == 12'b100000000000) begin
                signed_mag = 12'b011111111111;
            end
        end else begin
            signed_mag = D; // no change needed if positive
        end     
    end

endmodule

module leading_zeroes (D, E, F, fifth_bit);
   input [11:0] D;          
   output reg [2:0] E;      
   output reg [3:0] F;      
   output reg fifth_bit;    

   integer i;               
   integer j;               
   reg flag;         


   always @(*) begin
       i = 11;
       flag = 0;
       E = 8; // initial exponent value


       // go through leading zeros then calculate exponent
       while (i > 3) begin
            // found 1
           if (D[i] == 1) begin
               flag = 1; 
           end
           // decrement exponent for each leading zero
           if (flag == 0) begin
               E = E - 1; 
           end
           i = i - 1;
       end


       // find significand
       i = E + 3; 
       j = 3;     
       while (j >= 0) begin
           F[j] = D[i];
           i = i - 1;
           j = j - 1;
       end

       // get fifth bit to help with handling rounding
       if (i >= 0) begin
           fifth_bit = D[i];
       end else begin
           fifth_bit = 0; // default value
       end
   end
endmodule

module rounding(E_in, F_in, fifth_bit, E_out, F_out);

    // Inputs
    input [2:0] E_in;
    input [3:0] F_in;
    input fifth_bit;

    // Outputs
    output reg [2:0] E_out;
    output reg [3:0] F_out;

    always @(*) begin
        // set default outputs
        E_out = E_in;
        F_out = F_in;

        // if fifth bit is 1, round up
        if (fifth_bit == 1) begin
            // no overflow for significand
            if (F_in != 4'b1111) begin
                F_out += 1;
            end
            // Significand overflows, exponent doesnt overflow
            else if (E_in != 3'b111) begin
                E_out += 1;
                F_out = 4'b1000;
            end
        end
    end
endmodule