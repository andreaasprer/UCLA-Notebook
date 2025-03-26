// display values
parameter ZERO = 7'b1000000;
parameter ONE = 7'b1111001;
parameter TWO = 7'b0100100;
parameter THREE = 7'b0110000;
parameter FOUR = 7'b0011001;
parameter FIVE = 7'b0010010;
parameter SIX = 7'b0000010;
parameter SEVEN = 7'b1111000;
parameter EIGHT = 7'b0000000;
parameter NINE = 7'b0010000;
parameter OFF = 7'b1111111;

// anodes
parameter MINUTES_TENS_DIGIT = 4'b0111;
parameter MINUTES_ONES_DIGIT = 4'b1011;
parameter SECONDS_TENS_DIGIT = 4'b1101;
parameter SECONDS_ONES_DIGIT = 4'b1110;

// stopwatch digit limits
parameter MAX_ONES = 9;
parameter MAX_TENS = 5;

// clock counters
parameter TWO_HZ_COUNT = 25000000;
parameter ONE_HZ_COUNT = 50000000;
parameter FAST_COUNT = 200000;
parameter BLINK_COUNT = 37500000;
parameter DB_COUNT = 65535;
