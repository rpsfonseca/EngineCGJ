#include "Mat4.h"
#include "Vec4.h"
#include "Quat.h"
#include "Application.h"

#include <iostream>
#include <vector>
#include <string>

using namespace math;

void qtest1()
{

	Vec3 axis = { 0.0f, 1.0f, 0.0f};
	Quat q = Quat(90.0f, axis);
	std::cout << "   q = " << q << std::endl;

	Quat vi = { 7.0f, 0.0f, 0.0f, 0.0f };
	std::cout << "  vi = " << vi << std::endl;

	Quat qe = { 0.0f, 0.0f, -7.0f, 0.0f };
	std::cout << "  qe = " << qe << std::endl;

	Quat qinv = Quat::Inverse(q);
	//qClean(qinv);
	std::cout << "qinv = " << qinv << std::endl;

	Quat qf = (q * vi) * qinv;
	std::cout << "  qf = " << qf << std::endl;

	//assert(qEqual(qf, qe));
}

void qtest2()
{

	Vec3 axis = { 0.0f, 1.0f, 0.0f };
	Quat q = Quat(90.0f, axis);
	std::cout << "   q = " << q << std::endl;

	Vec4 vi = { 7.0f, 0.0f, 0.0f, 1.0f };
	std::cout << "vi = " << vi << std::endl;

	Vec4 ve = { 0.0f, 0.0f, -7.0f, 1.0f };
	std::cout << "ve = " << ve << std::endl;

	Mat4 m = Mat4();
	q.getMatrix(m);
	std::cout << " M = " << m << std::endl;

	Vec4 vf = m * vi;
	std::cout << "vf = " << vf << std::endl;


	//assert(vEqual(vf, ve));
}

void qtest3()
{
	Vec3 axis_x = { 1.0f, 0.0f, 0.0f };
	Vec3 axis_y = { 0.0f, 1.0f, 0.0f };
	Vec3 axis_z = { 0.0f, 0.0f, 1.0f };

	Quat qyaw900 = Quat(900.0f, axis_y);
	std::cout << "  qyaw900" << qyaw900 << std::endl;

	Quat qroll180 = Quat(180.0f, axis_x);
	std::cout << " qroll180" << qroll180 << std::endl;
	Quat qpitch180 = Quat(180.0f, axis_z);
	std::cout << "qpitch180" << qpitch180 << std::endl;
	Quat qrp = qpitch180 * qroll180;
	std::cout << "      qrp" << qrp << std::endl;
	Quat qpr = qroll180 * qpitch180;
	std::cout << "      qpr" << qpr << std::endl;

	Quat qi = { 1.0f, 0.0f, 0.0f, 0.0f }; // x-axis
	std::cout << "       qi" << qi << std::endl;
	Quat qe = { -1.0f, 0.0f, 0.0f, 0.0f };
	std::cout << "       qe" << qe << std::endl;

	Quat qyaw900inv = Quat::Inverse(qyaw900);
	Quat qfy = (qyaw900 * qi) *  qyaw900inv;
	std::cout << "       qy" << qfy << std::endl;
	//assert(qEqual(qe, qfy));

	Quat qrpinv = Quat::Inverse(qrp);
	Quat qfrp = (qrp * qi) * qrpinv;
	std::cout << "     qfrp" << qfrp << std::endl;
	//assert(qEqual(qe, qfrp));

	Quat qprinv = Quat::Inverse(qpr);
	Quat qfpr = (qpr * qi) * qprinv;
	std::cout << "     qfpr" << qfpr << std::endl;
	//assert(qEqual(qe, qfpr));
}

void qtest4()
{
	float thetai = 45.0f;
	Vec3 axis_i = { 0.0f, 1.0f, 0.0f };
	Quat q = Quat(thetai, axis_i);
	std::cout << thetai << " ";
	std::cout << "axis_i" << axis_i << std::endl;

	float thetaf;
	Vec3 axis_f;
	q.getRotate(thetaf, axis_f);
	std::cout << thetaf << " ";
	std::cout << "axis_f" << axis_f << std::endl;

	//assert(fabs(thetai - thetaf) < qThreshold && vEqual(axis_i, axis_f));
}

const void qPrintAngleAxis(const std::string& s, Quat& q)
{
	std::cout << s << " = [" << std::endl;

	float thetaf;
	Vec3 axis_f;
	q.getRotate(thetaf, axis_f);
	std::cout << "  angle = " << thetaf << std::endl;
	std::cout << "  axis" << axis_f << std::endl;
	std::cout << "]" << std::endl;
}

void qtest5()
{
	Vec3 axis = { 0.0f, 1.0f, 0.0f };
	Quat q0 = Quat(0.0f, axis);
	std::cout << "       q0" << q0 << std::endl;
	Quat q1 = Quat(90.0f, axis);
	std::cout << "       q1" << q1 << std::endl;
	Quat qe = Quat(30.0f, axis);
	std::cout << "       qe" << qe << std::endl;

	Quat qLerp0 = Quat::Lerp(q0, q1, 0.0f);
	std::cout << "  lerp(0)" << qLerp0 << std::endl;
	//assert(qEqual(qLerp0, q0));

	Quat qLerp1 = Quat::Lerp(q0, q1, 1.0f);
	std::cout << "  lerp(1)" << qLerp1 << std::endl;
	//assert(qEqual(qLerp1, q1));

	Quat qlerp = Quat::Lerp(q0, q1, 1 / 3.0f);
	std::cout << "lerp(1/3)" << qlerp << std::endl;
	qPrintAngleAxis("lerp(1/3)", qlerp);
}

void qtest6()
{
	Vec3 axis = { 0.0f, 1.0f, 0.0f };
	Quat q0 = Quat(0.0f, axis);
	std::cout << "       q0" << q0 << std::endl;
	Quat q1 = Quat(90.0f, axis);
	std::cout << "       q1" << q1 << std::endl;
	Quat qe = Quat(30.0f, axis);
	std::cout << "       qe" << qe << std::endl;

	Quat qSlerp0 = Quat::Slerp(q0, q1, 0.0f);
	std::cout << "  slerp(0)" << qSlerp0 << std::endl;
	//assert(qEqual(qSlerp0, q0));

	Quat qSlerp1 = Quat::Slerp(q0, q1, 1.0f);
	std::cout << "  slerp(1)" << qSlerp1 << std::endl;
	//assert(qEqual(qSlerp1, q1));

	Quat qslerp = Quat::Slerp(q0, q1, 1 / 3.0f);
	std::cout << "slerp(1/3)" << qslerp << std::endl;
	qPrintAngleAxis("slerp(1/3)", qslerp);
}

int main()
{
	Application app = Application(3, 3);
	app.setupApp();
	app.mainLoop();
	exit(EXIT_SUCCESS);

	/*qtest1();
	qtest2();*/
	/*qtest3();
	qtest4();
	qtest5();*/
	//qtest6();
}