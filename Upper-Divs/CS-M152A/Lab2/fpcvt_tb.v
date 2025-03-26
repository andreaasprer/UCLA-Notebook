`timescale 1ns / 1ps

module fpcvt_tb;

	// Inputs
	reg [11:0] D;

	// Outputs
	wire S;
	wire [2:0] E;
	wire [3:0] F;

	// Instantiate the Unit Under Test (UUT)
	fpcvt uut (
		.D(D), 
		.S(S), 
		.E(E), 
		.F(F)
	);
	
	initial begin
		D = 0;

		#100;
        
		// Test Cases of 12 bits
		// Normal positive values (round down)
		D = 12'b000000101101;
		#100;
		$display("Test:\t%b\nResult:\t%b %b %b\nExpected:\t%b %b %b", D, S, E, F, 1'b0, 3'b010, 4'b1011);
		$display("---------------------------------------------------");
		#100;
		D = 12'b000000101100;
		#100;
		$display("Test:\t%b\nResult:\t%b %b %b\nExpected:\t%b %b %b", D, S, E, F, 1'b0, 3'b010, 4'b1011);
		$display("---------------------------------------------------");
		#100;
		// Normal positive values (round up)
		D = 12'b000000101110;
		#100;
		$display("Test:\t%b\nResult:\t%b %b %b\nExpected:\t%b %b %b", D, S, E, F, 1'b0, 3'b010, 4'b1100);
		$display("---------------------------------------------------");
		#100;
		D = 12'b000000101111;
		#100;
		$display("Test:\t%b\nResult:\t%b %b %b\nExpected:\t%b %b %b", D, S, E, F, 1'b0, 3'b010, 4'b1100);
		$display("---------------------------------------------------");
		#100;
		// Normal negative value (round up)
		D = 12'b111111011001;
		#100;
		$display("Test:\t%b\nResult:\t%b %b %b\nExpected:\t%b %b %b", D, S, E, F, 1'b1, 3'b010, 4'b1010);
		$display("---------------------------------------------------");
		#100;
		// Normal negative value (round down)
		D = 12'b111111011101;
		#100;
		$display("Test:\t%b\nResult:\t%b %b %b\nExpected:\t%b %b %b", D, S, E, F, 1'b1, 3'b010, 4'b1001);
		$display("---------------------------------------------------");
		#100;
		// T_max
		D = 12'b011111111111;
		#100;
		$display("Test:\t%b\nResult:\t%b %b %b\nExpected:\t%b %b %b", D, S, E, F, 1'b0, 3'b111, 4'b1111);
		$display("---------------------------------------------------");
		#100;
		// T_min
		D = 12'b100000000000;
		#100;
		$display("Test:\t%b\nResult:\t%b %b %b\nExpected:\t%b %b %b", D, S, E, F, 1'b1, 3'b111, 4'b1111);
		$display("---------------------------------------------------");
		#100;
		// Exponent rounds
		D = 12'b000011111000;
		#100;
		$display("Test:\t%b\nResult:\t%b %b %b\nExpected:\t%b %b %b", D, S, E, F, 1'b0, 3'b101, 4'b1000);
		$display("---------------------------------------------------");
		#100;
		// -1
		D = 12'b111111111111;
		#100;
		$display("Test:\t%b\nResult:\t%b %b %b\nExpected:\t%b %b %b", D, S, E, F, 1'b1, 3'b000, 4'b0001);
		$display("---------------------------------------------------");
		#100;
		// 0
		D = 12'b000000000000;
		#100;
		$display("Test:\t%b\nResult:\t%b %b %b\nExpected:\t%b %b %b", D, S, E, F, 1'b0, 3'b000, 4'b0000);
		$display("---------------------------------------------------");
		#100;
		// Large positive number + significand overflows
		D = 12'b001111111111;
		#100;
		$display("Test:\t%b\nResult:\t%b %b %b\nExpected:\t%b %b %b", D, S, E, F, 1'b0, 3'b111, 4'b1000);
		$display("---------------------------------------------------");
		#100;
		// Large negative number + significand overflows
		D = 12'b110000000111;
		#100;
		$display("Test:\t%b\nResult:\t%b %b %b\nExpected:\t%b %b %b", D, S, E, F, 1'b1, 3'b111, 4'b1000);
		$display("---------------------------------------------------");
		#100;
	end
      
endmodule

