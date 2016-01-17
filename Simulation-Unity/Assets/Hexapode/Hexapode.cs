using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;

public class Hexapode : MonoBehaviour 
{
    [SerializeField]
    private GameObject goalSphere;
    [SerializeField]
    private UI ui;

    [SerializeField]
    private Leg leg1;
    [SerializeField]
    private Leg leg2;
    [SerializeField]
    private Leg leg3;
    [SerializeField]
    private Leg leg4;
    [SerializeField]
    private Leg leg5;
    [SerializeField]
    private Leg leg6;

    List<Leg> legs;

	// Use this for initialization
    void Start()
    {
        legs = new List<Leg>();

        legs.Add(leg1);
        legs.Add(leg2);
        legs.Add(leg3);
        legs.Add(leg4);
        legs.Add(leg5);
        legs.Add(leg6);

        leg1.initRelativePosition(leg1.transform.position, 0);
        leg2.initRelativePosition(leg2.transform.position, -60);
        leg3.initRelativePosition(leg3.transform.position, -120);
        leg4.initRelativePosition(leg4.transform.position, -180);
        leg5.initRelativePosition(leg5.transform.position, -240);
        leg6.initRelativePosition(leg6.transform.position, -300);

        //goToStanStill();
        StartCoroutine(goToPositionTripodCoroutine());
    }
	
	// Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
            Application.Quit();
	}

    private bool legsReachGoal()
    {
        foreach (Leg l in legs)
            if (!l.hasReachedGoal())
                return false;
        return true;
    }

    private void calcGoal()
    {
        legs.ForEach(l => l.setDirection(goalSphere.transform.localPosition.normalized));
    }

    private void goToStanStill()
    {
        legs.ForEach(l => l.goToCenterPosition());
    }

    public void requestTripodTransition()
    {
        StopAllCoroutines();
    }

    public void requestPairTransitiod()
    {
        StopAllCoroutines();
    }

    IEnumerator goToPositionTripodCoroutine()
    {
        calcGoal();

        StartCoroutine(goToDirectionPair(leg1, leg4));
        StartCoroutine(goToDirectionPair(leg5, leg2));
        StartCoroutine(goToDirectionPair(leg3, leg6));
        yield return new WaitForSeconds(0.3f);

        while (true)
        {
            yield return new WaitForSeconds(0.1f);
            calcGoal();
        }
    }

    IEnumerator goToPositionPairCoroutine()
    {
        calcGoal();

        StartCoroutine(goToDirectionPair(leg1, leg4));
        yield return new WaitForSeconds(0.3f);
        StartCoroutine(goToDirectionPair(leg5, leg2));
        yield return new WaitForSeconds(0.3f);
        StartCoroutine(goToDirectionPair(leg3, leg6));

        while (true)
        {
            yield return new WaitForSeconds(0.1f);
            calcGoal();
        }
    }

    IEnumerator goToDirectionPair(Leg l1, Leg l2)
    {
        float movementTime = 0.5f;

        l1.goToIdle(movementTime);
        yield return new WaitForSeconds(movementTime);
        while(true)
        {
            l1.goToStart(movementTime);
            yield return new WaitForSeconds(movementTime);

            l2.goToIdle(movementTime);
            l1.goToEnd(movementTime);
            yield return new WaitForSeconds(movementTime);

            l2.goToStart(movementTime);
            yield return new WaitForSeconds(movementTime);

            l1.goToIdle(movementTime);
            l2.goToEnd(movementTime);
            yield return new WaitForSeconds(movementTime);
        }
    }
}
