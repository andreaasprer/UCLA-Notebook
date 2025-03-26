`timescale 1ns / 1ps

module stopwatch_tb;

	// INPUTS
	reg clk;
	reg SEL;
	reg ADJ;
	reg RESET;
	reg PAUSE;

	// OUTPUTS
	wire [6:0] cathode;
	wire [3:0] anode;

	stopwatch uut (
		.clk(clk), 
		.SEL(SEL), 
		.ADJ(ADJ), 
		.RESET(RESET), 
		.PAUSE(PAUSE), 
		.cathode(cathode), 
		.anode(anode)
	);
	
	// Global clock
	always #2.5 clk = ~clk;

	initial begin
		// Initialize Inputs
		clk = 0;
		SEL = 0;
		ADJ = 0;
		RESET = 0;
		PAUSE = 0;

        // Reset stopwatch to 00:00		
		#100;
		RESET = 1;
        // Test debouncer
		#1100000;
		RESET = 0;
		#1100000;
		
		$display("Reset complete, beginning stopwatch");
		
		#500000000;
		
		$display("Normal mode finished\n");
		
		// Test adjustment minutes mode
		ADJ = 1;
		#1100000;
		#500000000;
		
		$display("Adjustment minute mode finished\n");
		
		// Test Adjustment Seconds mode
		SEL = 1;
		#1100000;
		#500000000;
		
		$display("Adjustment seconds mode finished\n");
		
	   // resume normal mode
		ADJ = 0;
		#1100000;
		#1000000000;
		
		$display("Turn off adjustment mode finished");
		
		// Pause test
		PAUSE = 1;
		#1100000;
		#100000000;
		PAUSE = 0;
		#1100000;
		
		$display("Pause test finished\n");
		
		// Unpause test
		PAUSE = 1;
		#1100000;
		#100000000;
		PAUSE = 0;
		#1100000;
		
		$display("Unpause test finished");
		
		// reset test
		RESET = 1;
		#1100000;
		
		$display("Reset test finished");
	end
      
endmodule