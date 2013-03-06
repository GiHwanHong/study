// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll			\
//   /cout:NamespaceDelegator.exe NamespaceDelegator.cs \
//   && NamespaceDelegator arg1 "arg2""
// End:
using System;
using System.Collections.Generic;

namespace MyNameSpace
{

public delegate bool IsWeirdNumber<T> (int number);

class NamespaceDelegator {
	public static bool MyIsEvenNumber(int number) {
		return (number % 2 == 0);
	}
	public static void Main() {
		var myNumbers = new List<int>();
		myNumbers.AddRange(new int [] { 0, 4, 5, 11, 12, 15, 16, 1412, 1413 });

		var wn = new IsWeirdNumber<int>(MyIsEvenNumber);
		Console.WriteLine("test(10) : {0}", wn(10));
		Console.WriteLine("test(11) : {0}", wn(11));

		// �븮�� ��ü�� ����ϴ� ���
		var pi = new Predicate<int>(wn);
		foreach (var number in myNumbers.FindAll(pi))
		{
			Console.WriteLine("even number : {0}", number);
		}

		// ���� �޼ҵ带 ����ϴ� ���
		foreach (var number in myNumbers.FindAll(delegate (int v) {
					return (v % 2 != 0);
				}))
		{
			Console.WriteLine("custom delegate number : {0}", number);
		}

		// ���� ǥ������ ����ϴ� ���
		foreach (var number in myNumbers.FindAll(i => ( i > 100 )))
		{
			Console.WriteLine("> 100 numbers: {0}", number);
		}
	}
}

} // namespace MyNameSpace
