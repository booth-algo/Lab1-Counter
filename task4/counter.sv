module counter #(
  parameter WIDTH = 8
)(
  // interface signals
  input  logic             clk,      // clock 
  input  logic             rst,      // reset 
  input  logic             en,       
  input  logic [WIDTH-1:0] v,        // value to preload
  output logic [WIDTH-1:0] count     // count output
);

always_ff @ (posedge en)
  if (rst)        count <= {WIDTH{1'b0}};
  else if (en)    count <= count + {{WIDTH-1{1'b0}},1'b1};

endmodule
