using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class AX12Manager : MonoBehaviour
{
  [SerializeField]
  private List<AX12> ax12List;

  public void SetGoal(int id, int goal)
  {
    if (id != 0xFE)
      ax12List[id].SetGoal(goal);
    else
      foreach (AX12 ax12 in ax12List)
        ax12.SetGoal(goal);
  }
}