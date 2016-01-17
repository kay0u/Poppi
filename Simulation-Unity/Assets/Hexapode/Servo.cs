using UnityEngine;
using System.Collections;

public class Servo : MonoBehaviour 
{
    Quaternion goal;
    Vector3 goalEuler;
    Vector3 rotation = Vector3.zero;//Keep track of the "real" angle
    float speed = 2f;

    private bool reachedTarget;
    public bool ReachedTarget
    { get { return reachedTarget; } }

    public void goTo(Vector3 angle)
    {
        goalEuler = angle;
        goal = Quaternion.Euler(angle);
        StopAllCoroutines();
        StartCoroutine(gotoCoroutine());
    }

    public void goToInTime(Vector3 angle, float time)
    {
        speed = 1 / time;
        goTo(angle);
    }

    public void goToAtSpeed(Vector3 angle, float s)
    {
        speed = 1;
        goTo(angle);
    }

    public void stop()
    {
        StopAllCoroutines();
    }

    IEnumerator gotoCoroutine()
    {
        transform.localRotation = Quaternion.Euler(rotation);
        Vector3 startRot = rotation;
        Vector3 previousRot = startRot;
        float startTime = Time.time;
        reachedTarget = false;

        while (true)
        {
            yield return null;
            rotation = Vector3.Lerp(startRot, goalEuler, (Time.time - startTime) * speed);
            transform.localRotation = Quaternion.Euler(rotation);

            if(previousRot == rotation)
            {
                reachedTarget = true;
                break;
            }
            previousRot = rotation;
        }
    }
}