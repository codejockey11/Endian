#include <iostream>
#include <Windows.h>

FILE* out;

class Endian
{
	public:

		static const char Little = 0;
		static const char Big = 1;

		Endian()
		{
			int i = 1;

			char* bytes = (char*)&i;

			machineType = Little;

			if (bytes[0] == 0x00)
			{
				machineType = Big;
			}
		}

		char GetMachineType()
		{
			return machineType;
		}

		char* ConvertLittleToBig(int n)
		{
			char* bytes = (char*)&n;

			memset(result, 0x00, 5);

			int y = 3;

			for (int x = 0; x < 4; x++)
			{
				result[y] = bytes[x];
				y--;
			}

			return result;
		}

		char* ConvertLittleToBig(char* bytes)
		{
			memset(result, 0x00, 5);

			int y = 3;

			for (int x = 0; x < 4; x++)
			{
				result[y] = bytes[x];
				y--;
			}

			return result;
		}

		char* ConvertBigToLittle(int n)
		{
			char* bytes = (char*)&n;

			memset(result, 0x00, 5);

			int y = 0;

			for (int x = 3; x > -1; x--)
			{
				result[y] = bytes[x];
				y++;
			}

			return result;
		}

		char* ConvertBigToLittle(char* bytes)
		{
			memset(result, 0x00, 5);

			int y = 0;

			for (int x = 3; x > -1; x--)
			{
				result[y] = bytes[x];
				y++;
			}

			return result;
		}

private:

		char result[5] = { 0x00, 0x00, 0x00, 0x00, 0x00 };

		char machineType = 0;

};

int main()
{
	Endian* e = new Endian();

	printf("Machine Type:");

	if (e->GetMachineType() == e->Little)
	{
		printf("little\r\n");
	}
	else
	{
		printf("big\r\n");
	}

	int x = 38;

	fopen_s(&out, "lendian.txt", "wb");

	fwrite(&x, sizeof(int), 1, out);

	fclose(out);

	fopen_s(&out, "lendian.txt", "rb");

	fread(&x, sizeof(int), 1, out);

	printf("int i:%04i\r\n", x);

	char* c = (char*)&x;
	printf("int stored as:");

	for (int l = 0; l < 4; l++)
	{
		printf("%02x ", c[l]);
	}

	printf("\r\n=============================\r\n");

	fclose(out);

	printf("Convert Little To Big\r\n");

	char* r = e->ConvertLittleToBig(x);

	printf("result:");

	for (int l = 0; l < 4; l++)
	{
		printf("%02x ", r[l]);
	}
	
	printf("\r\n");

	fopen_s(&out, "bendian.txt", "wb");

	fwrite(r, 4, 1, out);

	fclose(out);

	fopen_s(&out, "bendian.txt", "rb");

	char res[5];
	memset(res, 0x00, 5);

	fread(res, 4, 1, out);

	printf("read:");

	for (int l = 0; l < 4; l++)
	{
		printf("%02x ", res[l]);
	}

	printf("\r\nConvert Big To Little\r\n");

	r = e->ConvertBigToLittle(res);

	printf("result:");

	for (int l = 0; l < 4; l++)
	{
		printf("%02x ", r[l]);
	}

	printf("\r\n");

	int ii = *r;

	printf("int ii = *r;:%04i\r\n", ii);

	fclose(out);
}
