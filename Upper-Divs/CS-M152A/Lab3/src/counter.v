`timescale 1ns / 1ps

module counter(
    // INPUTS
	input clk_1hz,
	input clk_2hz,
	input sel,
	input adj,
	input rst,
	input pause,
	// Outputs
	output reg [3:0] minutes_tens,
	output reg [3:0] minutes_ones,
	output reg [3:0] seconds_tens,
	output reg [3:0] seconds_ones
);
	
	`include "stopwatch_constants.v"
	
	// check pause state
	reg is_paused = 0;
	
	// clock selector
	sel_adj adjust(.adj(adj), .clk_1hz(clk_1hz), .clk_2hz(clk_2hz), .which_clk(clk));
	
	always @(posedge pause) begin
		// set pause state
		is_paused = ~is_paused;
	end
	
	always @(posedge clk or posedge rst) begin
		if (rst) begin
			// reset values
			minutes_tens <= 0;
			minutes_ones <= 0;
			seconds_tens <= 0;
			seconds_ones <= 0;
		// adjustment mode
		end else if (adj && ~is_paused) begin
			if (~sel) begin
				// minutes ones place
				if (minutes_ones == MAX_ONES) begin
					minutes_ones <= 0;
					// minutes tens place
					if (minutes_tens == MAX_TENS) begin
						minutes_tens <= 0;
					end else begin
						minutes_tens <= minutes_tens + 1'b1;
					end
				end else begin
					minutes_ones <= minutes_ones + 1'b1;
				end
			end else begin
				// seconds ones place
				if (seconds_ones == MAX_ONES) begin
					seconds_ones <= 0;
					// seconds tens place
					if (seconds_tens == MAX_TENS) begin
						seconds_tens <= 0;
					end else begin
						seconds_tens <= seconds_tens + 1'b1;
					end
				end else begin
					seconds_ones <= seconds_ones + 1'b1;
				end
			end
		// Normal mode
		end else if (~adj && ~is_paused) begin
			// seconds ones
			if (seconds_ones == MAX_ONES) begin
				seconds_ones <= 0;
				// seconds tens
				if (seconds_tens == MAX_TENS) begin
					seconds_tens <= 0;
					// minutes ones
					if (minutes_ones == MAX_ONES) begin
						minutes_ones <= 0;
						// minutes tens
						if (minutes_tens == MAX_TENS) begin
							minutes_tens <= 0;
						end else begin
							minutes_tens <= minutes_tens + 1'b1;
						end
					end else begin
						minutes_ones <= minutes_ones + 1'b1;
					end
				end else begin
					seconds_tens <= seconds_tens + 1'b1;
				end
			end else begin
				seconds_ones <= seconds_ones + 1'b1;
			end
		end
	end
	
endmodule