`timescale 1ns / 1ps

module sel_adj(
    // INPUTS
    adj,
    clk_1hz,
    clk_2hz,

    // OUTPUT
    which_clk
);

    input adj,
    input clk_1hz,
    input clk_2hz,
    output which_clk;

    reg which_clk_temp;

    always @(*) begin
        // Adjustment mode
        if (adj) begin
            which_clk_temp = clk_2hz;
        end

        // Normal mode
        else begin
            which_clk_temp = clk_1hz;
        end
    end

    assign which_clk = which_clk_temp;

endmodule