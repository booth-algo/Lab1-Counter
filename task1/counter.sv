module counter #(
    parameter WIDTH = 8
)(
    // interface signals
    input   logic               clk,    // clock
    input   logic               rst,    // reset
    input   logic               en,     // counter enable
    output  logic [WIDTH-1:0]   count   //count output
);

always_ff @ (posedge clk, posedge rst) // specify clock circuit using flip flop behaviour
    /*Below are non-block assignments used in an always_ff block*/
    if (rst)    count <= {WIDTH{1'b0}}; // Concatenation operator to form WIDTH bits of '0'
    else        count <= count + {{WIDTH-1{1'b0}}, en}; // Concatenation to form WIDTH-1 bits with the LSB being the bit of the enable signal

    // 1'b0 means "1-bit wide binary constant with value of 0"
    // e.g., In parameter, we set WIDTH = 8, the result is 8'b00000001

endmodule
