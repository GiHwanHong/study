// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:exe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /main:TimerEventTest /out:TimerEventTest.exe *.cs\
//   && TimerEventTest"
// End:
using System;
using System.Timers;
class TimerHandlingClass {
	public void OnElapsed(Object sender, ElapsedEventArgs e) {
		Console.WriteLine("object handled event(data={0}) handled event!", data);
	}
	public int data;
}
class TimerEventTest {
	static void Main() {
		TimerHandlingClass thc = new TimerHandlingClass();
		thc.data = 18; // ��ü�� �� ��ü�� �´��� Ȯ��.
		Timer timer = new Timer();
		timer.Interval = 500;

		// ��ü�� ����Լ�
		timer.Elapsed += thc.OnElapsed;
		// �͸� �޼ҵ�(anonymous method) - full version
		timer.Elapsed += delegate (Object sender, ElapsedEventArgs e) {
			Console.WriteLine("Lambda delegator handled event!!!");
		};
		// �͸� �޼ҵ� - short version
		timer.Elapsed += delegate {
			Console.WriteLine("Simple Lambda delegator handled event!!!");
		};
		// �����Լ�
		timer.Elapsed += TesterHandler;

		timer.Start();
		Console.ReadLine();
	}
	public static void TesterHandler(Object sender, ElapsedEventArgs e) {
		Console.WriteLine("TesterHandler handled event!!!");
	}
}
