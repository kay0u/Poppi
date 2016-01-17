using UnityEngine;
using System.Collections;

public class Leg : MonoBehaviour
{
    [SerializeField]
    private UI ui;
    [SerializeField]
    private Servo gamma;
    [SerializeField]
    private Servo alpha;
    [SerializeField]
    private Servo beta;
    [SerializeField]
    private GameObject tibia;
    [SerializeField]
    private GameObject femur;
    [SerializeField]
    private Transform sphereGoal;
    [SerializeField]
    private Transform startSphere;
    [SerializeField]
    private Transform endSphere;
    [SerializeField]
    private Transform gotoDirCenterTransform;

    private float tibiaLength;
    private float femurLength;
    private float angleToHexapod;
    private float speed;

    Vector3 goal;
    Vector3 distanceToHexapod;
    Vector3 gotoDirCenterPosition;

    Vector3 startPosition;
    Vector3 endPosition;
    Vector3 idlePosition;

	// Use this for initialization
    void Awake()
    {
        speed = 1;
        tibiaLength = 4f;
        femurLength = 4f;
        gotoDirCenterPosition = gotoDirCenterTransform.position;
	}

    void Update()
    {
    }

    public void initRelativePosition(Vector3 dist, float angle)
    {
        distanceToHexapod = dist;
        angleToHexapod = Mathf.Deg2Rad * angle;
    }

    private Vector3 hexapodSpaceToLocalSpace(Vector3 pos)
    {
        Vector3 localPos;
        pos -= distanceToHexapod;
        localPos.x = Mathf.Cos(angleToHexapod) * pos.x + Mathf.Sin(angleToHexapod) * pos.z;
        localPos.z = Mathf.Cos(angleToHexapod) * pos.z - Mathf.Sin(angleToHexapod) * pos.x;
        localPos.y = pos.y;

        return localPos;
    }

    public void setDirection(Vector3 dir)
    {
        startPosition = hexapodSpaceToLocalSpace(gotoDirCenterPosition + dir * speed);
        endPosition = hexapodSpaceToLocalSpace(gotoDirCenterPosition - dir * speed);
        idlePosition = hexapodSpaceToLocalSpace(gotoDirCenterPosition + new Vector3(0, 3, 0));

        startSphere.transform.localPosition = startPosition;
        endSphere.transform.localPosition = endPosition;
    }

    public void stop()
    {
        StopAllCoroutines();
        gamma.stop();
        alpha.stop();
        beta.stop();
    }

    public void goToIdle(float time)
    {
        goToInTime(idlePosition, time);
    }

    public void goToStart(float time)
    {
        goToInTime(startPosition, time);
    }

    public void goToEnd(float time)
    {
        goToInTime(endPosition, time);
    }

    public void goToCenterPosition()
    {
        stop();
        goTo(hexapodSpaceToLocalSpace(gotoDirCenterPosition));
    }

    public void goToDirection()
    {
        stop();
        StartCoroutine(goToDirectionCoroutine());
    }

    private IEnumerator goToDirectionCoroutine()
    {
        float movementTime = 0.5f;
        goToInTime(idlePosition, movementTime);
        while (!hasReachedGoal())
            yield return null;
        while(true)
        {
            goToInTime(startPosition, movementTime);
            while (!hasReachedGoal())
                yield return null;
            goToInTime(endPosition, movementTime);
            while (!hasReachedGoal())
                yield return null;
            yield return new WaitForSeconds(0.5f);
            goToInTime(idlePosition, movementTime);
            while (!hasReachedGoal())
                yield return null;
        }
    }

    private Vector3 processIK(Vector3 pos)
    {
        goal = pos;
        sphereGoal.localPosition = goal;
        float distanceToTarget = Vector3.Distance(goal, Vector3.zero);
        float alpha1 = Mathf.Acos(-goal.y / distanceToTarget);
        float alpha2 = Mathf.Acos((Mathf.Pow(tibiaLength, 2) - Mathf.Pow(femurLength, 2) - Mathf.Pow(distanceToTarget, 2)) / (-2 * femurLength * distanceToTarget));
        float beta1 = Mathf.Acos((Mathf.Pow(distanceToTarget, 2) - Mathf.Pow(tibiaLength, 2) - Mathf.Pow(femurLength, 2)) / (-2 * tibiaLength * femurLength));

        float gammaGoal = Mathf.Rad2Deg * Mathf.Atan2(goal.x, goal.z) + 150;
        float alphaGoal = -Mathf.Rad2Deg * (alpha1 + alpha2 - Mathf.PI / 2) + 60;
        float betaGoal = Mathf.Rad2Deg * (-beta1 + Mathf.PI);
        return new Vector3(gammaGoal, alphaGoal, betaGoal);
    }

    public void goTo(Vector3 pos)
    {
        Vector3 rots = processIK(pos);
        gamma.goTo(new Vector3(0, rots.x, 0));
        alpha.goTo(new Vector3(rots.y, 0, 0));
        beta.goTo(new Vector3(rots.z, 0, 0));
    }

    public void goToInTime(Vector3 pos, float time)
    {
        Vector3 rots = processIK(pos);
        
        gamma.goToInTime(new Vector3(0, rots.x, 0), time);
        alpha.goToInTime(new Vector3(rots.y, 0, 0), time);
        beta.goToInTime(new Vector3(rots.z, 0, 0), time);
    }

    public void goToAtSpeed(Vector3 pos, float s)
    {
        Vector3 rots = processIK(pos);

        gamma.goToAtSpeed(new Vector3(0, rots.x, 0), s);
        alpha.goToAtSpeed(new Vector3(rots.y, 0, 0), s);
        beta.goToAtSpeed(new Vector3(rots.z, 0, 0), s);
    }

    public bool hasReachedGoal()
    {
        return (gamma.ReachedTarget && alpha.ReachedTarget && beta.ReachedTarget);
    }
}
