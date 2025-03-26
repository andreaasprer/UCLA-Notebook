`timescale 1ns / 1ps

module create_display(
    // INPUTS
    input clk_fast,
    input clk_blink,
    input sel, input adj,
    input [6:0] minutes_tens_cathode,
	input [6:0] minutes_ones_cathode,
	input [6:0] seconds_tens_cathode,
	input [6:0] seconds_ones_cathode,
    
    //OUTPUTS
	output  [6:0] cathode,
	output  [3:0] anode
);

    `include "stopwatch_constants.v"

	// temporaries
	reg [1:0] switch  = 2'b00;
	reg [6:0] cathode_temp;
	reg [3:0] anode_temp;

	always @(posedge clk_fast) begin
		if (switch == 0) begin
			switch <= switch + 2'b1;
			anode_temp <= 4'b0111;
			// adjust minutes tens
			if (adj && !sel) begin
				if (clk_blink) begin
					cathode_temp <= minutes_tens_cathode;
			end
			else begin
				cathode_temp <= OFF;
			end
		end
		// dont change minutes
		else begin
			cathode_temp <= minutes_tens_cathode;
		end
	end
	else if (switch == 1) begin
		switch <= switch + 2'b1;
		anode_temp <= 4'b1011;
		// adjust minutes ones
		if (adj && !sel) begin
			if (clk_blink) begin
				cathode_temp <= minutes_ones_cathode;
			end
			else begin
				cathode_temp <= OFF;
			end
		end
		else begin
			cathode_temp <= minutes_ones_cathode;
		end
	end
	else if (switch == 2) begin
		switch <= switch + 2'b1;
		anode_temp <= 4'b1101;
			// seconds
			if (adj && sel) begin
				if (clk_blink) begin
					cathode_temp <= seconds_tens_cathode;
				end
				else begin
					cathode_temp <= OFF;
				end
			end
			// not Adjust Clock Mode, or adjusting minutes, seconds don't change
			else begin
				cathode_temp <= seconds_tens_cathode;
			end
		end 
		else if (switch == 3) begin
			switch <= 2'b0;
			anode_temp <= 4'b1110;
			// adjust ones seconds
			if (adj && sel) begin
				if (clk_blink) begin
					cathode_temp <= seconds_ones_cathode;
				end
				else begin
					cathode_temp <= OFF;
				end
			end
			// not Adjust Clock Mode, or adjusting minutes, seconds don't change
			else begin
				cathode_temp <= seconds_ones_cathode;
			end
		end
	end

    
    assign cathode = cathode_temp;
	assign anode = anode_temp;
    
	
	

endmodule