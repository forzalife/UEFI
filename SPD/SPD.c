//**************************************
//	Hiwen 2016.04.07 
//	ͨ�� SMBus Protocol ��ȡ SPD ��Ϣ��
//	Byte Read SPD data(256bytes)
//ע������ *.inf ��ӵ� MdeModulePkg.dsc��
//	1. ���滷���£����д� *.efi �Ῠס��
//	2. ��Ҫ�� Shell U����ִ�У�����
//**************************************

#include <Uefi.h>
#include <Library/UefiLib.h>	//Print()
#include <Library/UefiApplicationEntryPoint.h>
#include <Library\IoLib.h>		//IoWrite8() & IoRead8()

// �궨��
// SMBus Base Address ��Ҫ����ʵ�ʵ�����EDS Spec.
// SPD slave Address ��Ҫ�ο� WH �ĵ�·���.
#define	SMB_BASE	0xF040	//PCI - B00D31F03 0ffset = 20h-23h
#define	SPD_Address	0xA0

EFI_STATUS
EFIAPI
SPDMain (
	IN EFI_HANDLE		ImageHandle,
	IN EFI_SYSTEM_TABLE	*SystemTable
	)
{	
	EFI_STATUS	Status	=	EFI_SUCCESS ;
	UINT8		i,j,SPD_OFFSET,DATA;
    
    for(i=0; i<16; i++)
    {
	    for(j=0;j<16;j++)
	    {
		    SPD_OFFSET = i*16+j;
		    
		    IoWrite8(SMB_BASE+0x00, 0xFF); //Clear to 0x40
		    
			//Wait - Make sure "SMB_BASE+0x00" = "0x40" to continue
		    while( (IoRead8(SMB_BASE+0x00)&0x40) != 0x40); 
			
		    IoWrite8(SMB_BASE+0x04, SPD_Address+1); //(Slave Address + 1) to Read way
		    IoWrite8(SMB_BASE+0x03, SPD_OFFSET); //Read Which SPD offset
		    IoWrite8(SMB_BASE+0x02, 0x48); //Byte Read Command
		    
			//Wait - Make sure "SMB_BASE+0x00" = "0x42" to continue, read DATA
		    while( (IoRead8(SMB_BASE+0x00)&0x42) != 0x42); 
			
		    DATA = IoRead8(SMB_BASE+0x05); //Read the SPD data
		    
		    Print(L" %2X",DATA);
	    }
        
		Print(L"\n");
    } 
	  
    IoWrite8(SMB_BASE+0x00, 0xFF); //Clear to 0x40
    while( (IoRead8(SMB_BASE+0x00)&0x40) != 0x40); //Make sure clear
    return Status;	
}
