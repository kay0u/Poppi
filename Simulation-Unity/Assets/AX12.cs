using UnityEngine;
using System.Collections;

public class AX12 : MonoBehaviour {

  [SerializeField]
  private Vector3 axis;

  private int rotation = 0;
  private bool reachedTarget = true;
  private float speed = 1f;

  public void SetGoal(int goal)
  {
    rotation = goal;

    StopAllCoroutines();
    StartCoroutine(gotoCoroutine());
  }

  IEnumerator gotoCoroutine()
  {
    Vector3 startRot = transform.rotation.eulerAngles;
    Vector3 previousRot = startRot;
    float startTime = Time.time;
    reachedTarget = false;

    while (true)
    {
      yield return null;
      transform.rotation = Quaternion.Euler(Vector3.Lerp(startRot, startRot + axis * rotation, (Time.time - startTime) * speed));

      if (previousRot == transform.rotation.eulerAngles)
      {
        reachedTarget = true;
        break;
      }
      previousRot = transform.rotation.eulerAngles;
    }
  }
}
