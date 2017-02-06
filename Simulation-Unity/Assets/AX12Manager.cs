using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class AX12Manager : ReceiverAbstract
{
  [SerializeField]
  private List<AX12> ax12List;

	public override void Receive(string[] order)
	{
		switch (order [1]) {
		case "move":
			SetGoal (int.Parse(order [2]), int.Parse(order [3]));
			break;
		default:
			break;
		}
	}

  private void SetGoal(int id, int goal)
  {
    if (id != 0xFE)
      ax12List[id].SetGoal(goal);
    else
      foreach (AX12 ax12 in ax12List)
        ax12.SetGoal(goal);
  }
}