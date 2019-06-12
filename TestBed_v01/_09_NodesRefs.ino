M_Node_Input inc_1 = M_Node_Input();
M_Node_Input dec_1 = M_Node_Input();
M_Node_Input rst_1 = M_Node_Input();
M_Node_Input hld_1 = M_Node_Input();
M_Node_Input pse_1 = M_Node_Input();
M_Node_Input clr_1 = M_Node_Input();

M_Node_Output o0_1 = M_Node_Output();
M_Node_Output o1_1 = M_Node_Output();
M_Node_Output o2_1 = M_Node_Output();
M_Node_Output o3_1 = M_Node_Output();
M_Node_Output o4_1 = M_Node_Output();
M_Node_Output o5_1 = M_Node_Output();
M_Node_Output o6_1 = M_Node_Output();
M_Node_Output o7_1 = M_Node_Output();
M_Node_Output o8_1 = M_Node_Output();
M_Node_Output o9_1 = M_Node_Output();
M_Node_Output o10_1 = M_Node_Output();
M_Node_Output o11_1 = M_Node_Output();
M_Node_Output o12_1 = M_Node_Output();
M_Node_Output o13_1 = M_Node_Output();
M_Node_Output o14_1 = M_Node_Output();
M_Node_Output o15_1 = M_Node_Output();

void MapNodes()
{
  inc_1.Prep(0, 0, 0, 0);
  dec_1.Prep(0, 1, 0, 1);
  rst_1.Prep(0, 4, 0, 4);
  hld_1.Prep(0, 5, 0, 5);
  pse_1.Prep(0, 6, 0, 6);
  clr_1.Prep(0, 7, 0, 7);

  o0_1.Prep(1, 0, 1, 0);
  o1_1.Prep(1, 1, 1, 1);
  o2_1.Prep(1, 2, 1, 2);
  o3_1.Prep(1, 3, 1, 3);
  o4_1.Prep(1, 4, 1, 4);
  o5_1.Prep(1, 5, 1, 5);
  o6_1.Prep(1, 6, 1, 6);
  o7_1.Prep(1, 7, 1, 7);
  o8_1.Prep(2, 0, 2, 0);
  o9_1.Prep(2, 1, 2, 1);
  o10_1.Prep(2, 2, 2, 2);
  o11_1.Prep(2, 3, 2, 3);
  o12_1.Prep(2, 4, 2, 4);
  o13_1.Prep(2, 5, 2, 5);
  o14_1.Prep(2, 6, 2, 6);
  o15_1.Prep(2, 7, 2, 7);
}
