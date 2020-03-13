#pragma once
#include "xlib.h"

class RefObjCommon
{
private:
	char vftable_ptr[4]; //0x0000 | we don't need that shit atm
	char pad_0004[4]; //0x0004
	long long ObjID; //0x0008
	std::string CodeName; //0x0010
	std::string Name; //0x002C
	std::string OrgObjCodeName; //0x0048
	std::string DescStrID; //0x0064
	USHORT TID; //0x0080
	char pad_0082[2]; //0x0082
	char unk_0084[4]; //0x0084
	BYTE Country; //0x0088
	BYTE Rarity; //0x0089
	char pad_008A[2]; //0x008A
	char unk_008C[4]; //0x008C
	char pad_0090[4]; //0x0090
	char unk_0094[8]; //0x0094
	UINT Price; //0x009C
	UINT CostRepair; //0x00A0
	UINT CostRevive; //0x00A4
	UINT CostBorrow; //0x00A8
	UINT KeepingFee; //0x00AC
	UINT SellPrice; //0x00B0
	int ReqLevelType1; //0x00B4
	BYTE ReqLevel1; //0x00B8
	char pad_00B9[3]; //0x00B9
	int ReqLevelType2; //0x00BC
	BYTE ReqLevel2; //0x00C0
	char pad_00C1[3]; //0x00C1
	int ReqLevelType3; //0x00C4
	BYTE ReqLevel3; //0x00C8
	char pad_00C9[3]; //0x00C9
	int ReqLevelType4; //0x00CC
	BYTE ReqLevel4; //0x00D0
	char pad_00D1[3]; //0x00D1
	int MaxContain; //0x00D4
	USHORT RegionID; //0x00D8
	short Direction; //0x00DA
	int OffsetX; //0x00DC
	int OffsetY; //0x00E0
	int OffsetZ; //0x00E4
	int Scale; //0x00E8
	int BCHeight; //0x00EC
	int BCRadius; //0x00F0
	std::string AssocFileObj; //0x00F4
	std::string AssocFileDrop; //0x0110
	std::string AssocFileIcon; //0x012C
	std::string AssocFile1; //0x0148
	std::string AssocFile2; //0x0164
	char pad_0180[4]; //0x0180
	UINT Link; //0x0184
};

class RefObjItem : public RefObjCommon
{
public:
	char pad_0188[280]; //0x0188 | fuck all that, i want params n their descs
	int Param1; //0x02A0
	std::string Desc1; //0x02A4
	int Param2; //0x02C0
	std::string Desc2; //0x02C4
	int Param3; //0x02E0
	std::string Desc3; //0x02E4
	int Param4; //0x0300
	std::string Desc4; //0x0304
	int Param5; //0x0320
	std::string Desc5; //0x0324
	int Param6; //0x0340
	std::string Desc6; //0x0344
	int Param7; //0x0360
	std::string Desc7; //0x0364
	int Param8; //0x0380
	std::string Desc8; //0x0384
	int Param9; //0x03A0
	std::string Desc9; //0x03A4
	int Param10; //0x03C0
	std::string Desc10; //0x03C4
	int Param11; //0x03E0
	std::string Desc11; //0x03E4
	int Param12; //0x0400
	std::string Desc12; //0x0404
	int Param13; //0x0420
	std::string Desc13; //0x0424
	int Param14; //0x0440
	std::string Desc14; //0x0444
	int Param15; //0x0460
	std::string Desc15; //0x0464
	int Param16; //0x0480
	std::string Desc16; //0x0484
	int Param17; //0x04A0
	std::string Desc17; //0x04A4
	int Param18; //0x04C0
	std::string Desc18; //0x04C4
	int Param19; //0x04E0
	std::string Desc19; //0x04E4
	int Param20; //0x0500
	std::string Desc20; //0x0504
};

class CInstanceObj
{
public:
	char pad_0000[24]; //0x0000
	RefObjItem* objitem; //0x0018
};

class CGItem
{
public:
	char pad_0000[52]; //0x0000
	CInstanceObj* insta_obj; //0x0034
};