`timescale 1ns / 1ps

module clock_divider(
    // INPUTS
    input clk,
    input rst,

    // OUTPUTS
    output reg clk_2hz,
    output reg clk_1hz,
    output reg clk_fast,
    output reg clk_blink
);

    `include "stopwatch_constants.v"

    // counters for the clocks
    reg [31:0] counter_2hz = 0;
    reg [31:0] counter_1hz = 0;
    reg [31:0] counter_fast = 0;
    reg [31:0] counter_blink = 0;

    always @(posedge clk or posedge rst) begin
        // reset clock signals if reset is clicked
        if (rst) begin
            counter_2hz <= 0;
            counter_1hz <= 0;
            counter_fast <= 0;
            counter_blink <= 0;            

            clk_2hz <= 0;
            clk_1hz <= 0;
            clk_fast <= 0;
            clk_blink <= 0;           
        end 
        // increment clocks
        else begin
            counter_2hz <= counter_2hz + 1;
            counter_1hz  <= counter_1hz + 1;
            counter_fast <= counter_fast + 1;
            counter_blink <= counter_blink + 1; 

            // verify if counters havent passed the constants
            if (counter_2hz >= TWO_HZ_COUNT) begin
                counter_2hz <= 0;
                clk_2hz <= ~clk_2hz;
            end           
            if (counter_1hz >= ONE_HZ_COUNT) begin
                counter_1hz <= 0;
                clk_1hz <= ~clk_1hz;
            end
            if (counter_fast >= FAST_COUNT) begin
                counter_fast <= 0;
                clk_fast <= ~clk_fast;
            end
            if (counter_blink >= BLINK_COUNT) begin
                counter_blink <= 0;
                clk_blink <= ~clk_blink;
            end                        
        end
    end
endmodule