// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll		\
//   /main:ExtensionTest /out:ExtensionTest.exe ExtensionTest.cs	\
//   && ExtensionTest arg1 "arg2""
// End:
using System;

// namespace ���� ���ǵ� Extension Method ��
// ����ϱ� ���� �� �ʿ��� using!!!!!
using MyExtension;

namespace MyExtension
{

// Extension Method �� �ݵ�� static class �� ���ǵǾ�� ��.
public static class MyExtensionClass
{
	// ��� Extension Method �� �ᱹ static��.
	// (static class �� ���ǵǹǷ�....)
	public static void DoSomeExtension(
			// �� �޼ҵ�� System.Object �� �߰��Ǵ� �޼ҵ����� �˸�
			this Object obj,
			// ���� �޼ҵ��� ù��° ����
			int additionalArg
		)
	{
		Console.WriteLine("Type:{0}, AdditionalArg:{1}",
						  obj.GetType().Name, additionalArg);
	}
}

}

class ExtensionTest
{
	public static void Main()
	{
		int myInt = 10;
		myInt.DoSomeExtension(12);
	}
}