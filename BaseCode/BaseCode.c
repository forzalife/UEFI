//************************
// �������һ�� UEFI ʵ��
//************************

#include <Uefi.h>
#include <Library\UefiLib.h>  //Print()

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE			ImageHandle,
  IN EFI_SYSTEM_TABLE	*SystemTable
  )
{
  //Print
  //Use UefiLib Print API to print string to UEFI console
  Print(L"Hi,everyone. This is the most basic UEFI APP!\n");
  Print(L"Are OK?\n");

  //ConOut
  //�������
  //���к���һ�������ǽ���ǰһ�е��ַ�׷�ӣ�
  SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\n");
  SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello\n");
  SystemTable->ConOut->OutputString(SystemTable->ConOut, L"world!\n");
  SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Are");
  SystemTable->ConOut->OutputString(SystemTable->ConOut, L"you");
  SystemTable->ConOut->OutputString(SystemTable->ConOut, L"OK?");

  return EFI_SUCCESS;
}
