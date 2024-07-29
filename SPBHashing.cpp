#include <iostream>
#include <string> 
#include <bitset>
#include <sstream>
#include <vector> 
#include <cstring>
#include <iomanip>
// Assuming you have these classes defined elsewhere
// with their respective Hash functions implemented.
namespace SPBHashing
{

	class SPB128
	{
	public:
		static const uint32_t GodKey = 0x300AE7F5;

		static std::string Hash(const std::string& message)
		{
			uint32_t e1 = 0x76662797;
			uint32_t e2 = 0xA2F0528E;
			uint32_t e3 = 0x2E9A9A9C;
			uint32_t e4 = 0x663085B9;
			uint32_t e5 = 0xED51D495;
			uint32_t e6 = 0x6F4DBBAC;
			uint32_t e7 = 0x7D43ADBE;
			uint32_t e8 = 0xB6A6A797;
			uint32_t e9 = 0xED51D495;
			uint32_t e10 = 0xB6A6A797;
			uint32_t e11 = 0x2630D28E;
			uint32_t e12 = 0xAF43ADC1;

			uint32_t Angels[24] = {
				0x40079CB5, 0x084DD54F, 0xB74D07D9, 0xAF4D84B7, 0x19218496, 0x2811AD87,
				0xAD4DD4A1, 0xA80D9D94, 0x3587D960, 0xB0078E69, 0xB00D84CC, 0x058F9031,
				0x280DA810, 0x058FA3C8, 0xAE9A7407, 0x2551AD8F, 0x374DBF7A, 0x258FA186,
				0x8741D3E3, 0xA312D4F0, 0xF8189A87, 0xB5DABDD3, 0x264FBDD3, 0x9BDABDD3
			};

			uint32_t key[114] = {
				0x374D07E4,0xA697DC04,0x26811752,0xA89107E4,0x255107E4,0x738EDC04
,0x680D07E4,0x738EDC04,0x380DDC04,0x088BE8EA,0xAD473E42,0x2911ACEA
,0x800D07E4,0x3F4D0755,0x380AE804,0xA61107E4,0x255107E4,0x3306FBE4
,0x2E90A0AC,0x259249E2,0x738EDC04,0x380AE804,0x260AE804,0xAB0DDC04
,0x374D07E4,0x2B0D07E4,0xAB0FFBE4,0x068D07E4,0xB00CDC04,0x380CDC04
,0x2551A643,0x0006E804,0x680D07E4,0x802B04FB,0xA75199AD,0x25904500
,0xAD5107E4,0x2D920DDD,0xA80FFBE4,0x3F4D8F00,0xB007BAD4,0x2617DC04
,0xB006E804,0x380AE804,0xA80D07E4,0x680D07E4,0xED51D495,0x3746E804
,0x380AE804,0x2D9245F6,0x281107E4,0xA58EDC04,0xA60AE804,0xB80FFBE4
,0x800D07E4,0x281107E4,0x375107E4,0x260AE804,0x374AE804,0x3006FBE4
,0xA806FBE4,0xB605FBE4,0x300CDC04,0x2686E804,0xA58EDC04,0x280D07E4
,0x300CDC04,0xB80DDC04,0x375107E4,0x261107E4,0xAE44F50C,0xB617DC04
,0x254AE804,0x255107E4,0x0843CC04,0x080CDC04,0x255107E4,0xA60AE804
,0xA61107E4,0xA74B279F,0x273EB7E4,0x080CDC04,0x261107E4,0x080CDC04
,0xB81107E4,0xAF5107E4,0x680D07E4,0x280D07E4,0x3806E804,0xA817DC04
,0x2605FBE4,0x8821CC04,0xAE1107E4,0x2B0D07E4,0x2443CC04,0xB00CDC04
,0x080D07E4,0x2F41CC04,0xA80DDC04,0xA74D07E4,0x080D07E4,0x273EB7E4
,0xA74D07E4,0xAD84FBE4,0x673CCC04,0x2807C009,0x255107E4,0x330CDC04
,0x884D07E4,0xA89107E4,0x255107E4,0x260AE804,0x280CDC04,0xA61107E4
			};

			std::ostringstream FirstTextByte;
			std::ostringstream FirstTextlength;

			for (char c : message)
			{
				FirstTextByte << std::bitset<8>(c);
			}
			int FirstTextByte_length = FirstTextByte.str().length();
			FirstTextByte << '1';
			FirstTextByte << '1';
			FirstTextByte << '0';
			while ((FirstTextByte.str().length() % 768) != 704)
			{
				FirstTextByte << '0';
			}
			FirstTextlength << std::bitset<64>(GodKey + FirstTextByte_length);
			FirstTextByte << FirstTextlength.str();

			//----------------------------------------

			int TempBytelength = FirstTextByte.str().length() / 768;
			std::vector<std::string> TempByteArray(TempBytelength);
			for (int i = 0, k = 0; i < FirstTextByte.str().length(); i += 768, k++)
			{
				TempByteArray[k] = FirstTextByte.str().substr(i, 768);
			}

			for (int x = 0; x < TempBytelength; x++)
			{
				uint32_t AngelArray[24];

				uint32_t splitByte[24];
				for (int i = 0, k = 0; i < TempByteArray[x].length(); i += 32, k++)
				{
					splitByte[k] = std::stoul(TempByteArray[x].substr(i, 32), nullptr, 2);
				}

				for (int i = 0; i <= 23; i++)
				{
					AngelArray[i] = (splitByte[i] + Angels[i % 24]);
				}

				for (int i = 0; i <= 23; i++)
				{
					AngelArray[(i + 2) % 24] = AngelArray[(i + 2) % 24] + ((AngelArray[i]) + (AngelArray[(i + 1) % 24]));
					Angels[(i + 23) % 24] = AngelArray[(i + 2) % 24];
				}
			}

			for (int i = 0; i < 38; i++)
			{
				uint32_t temp1 = e1 + (Angels[i % 24] ^ key[i]) + ((e5 << 9) | (e5 >> 23));
				uint32_t temp2 = e6 + (Angels[(i + 8) % 24] ^ key[i + 38]) + ((e2 << 8) | (e2 >> 24));
				uint32_t temp3 = e9 + (Angels[(i + 16) % 24] ^ key[i + 76]) + ((e8 << 7) | (e8 >> 25));

				e1 = e2; e2 = e3; e3 = e4; e4 = e5 + temp1;
				e5 = e6; e6 = e7; e7 = e8; e8 = e9 + temp2;
				e9 = e10; e10 = e11; e11 = e12; e12 = e1 + temp3;
			}

			std::ostringstream result;
			result << std::hex << (e1 + e2 + e3) << (e4 + e5 + e6) << (e7 + e8 + e9) << (e10 + e11 + e12);
			return result.str();
		}
	};

	class SPB192
	{
	public:
		static const uint32_t GodKey = 0x300AE7F5;

		static std::string Hash(const std::string& message)
		{
			uint32_t e1 = 0x76662797;
			uint32_t e2 = 0xA2F0528E;
			uint32_t e3 = 0x2E9A9A9C;
			uint32_t e4 = 0x663085B9;
			uint32_t e5 = 0xED51D495;
			uint32_t e6 = 0x6F4DBBAC;
			uint32_t e7 = 0x7D43ADBE;
			uint32_t e8 = 0xB6A6A797;
			uint32_t e9 = 0xED51D495;
			uint32_t e10 = 0xB6A6A797;
			uint32_t e11 = 0x2630D28E;
			uint32_t e12 = 0xAF43ADC1;

			uint32_t Angels[24] = {
				0x40079CB5, 0x084DD54F, 0xB74D07D9, 0xAF4D84B7, 0x19218496, 0x2811AD87,
				0xAD4DD4A1, 0xA80D9D94, 0x3587D960, 0xB0078E69, 0xB00D84CC, 0x058F9031,
				0x280DA810, 0x058FA3C8, 0xAE9A7407, 0x2551AD8F, 0x374DBF7A, 0x258FA186,
				0x8741D3E3, 0xA312D4F0, 0xF8189A87, 0xB5DABDD3, 0x264FBDD3, 0x9BDABDD3
			};

			uint32_t key[114] = {
				0x374D07E4,0xA697DC04,0x26811752,0xA89107E4,0x255107E4,0x738EDC04
,0x680D07E4,0x738EDC04,0x380DDC04,0x088BE8EA,0xAD473E42,0x2911ACEA
,0x800D07E4,0x3F4D0755,0x380AE804,0xA61107E4,0x255107E4,0x3306FBE4
,0x2E90A0AC,0x259249E2,0x738EDC04,0x380AE804,0x260AE804,0xAB0DDC04
,0x374D07E4,0x2B0D07E4,0xAB0FFBE4,0x068D07E4,0xB00CDC04,0x380CDC04
,0x2551A643,0x0006E804,0x680D07E4,0x802B04FB,0xA75199AD,0x25904500
,0xAD5107E4,0x2D920DDD,0xA80FFBE4,0x3F4D8F00,0xB007BAD4,0x2617DC04
,0xB006E804,0x380AE804,0xA80D07E4,0x680D07E4,0xED51D495,0x3746E804
,0x380AE804,0x2D9245F6,0x281107E4,0xA58EDC04,0xA60AE804,0xB80FFBE4
,0x800D07E4,0x281107E4,0x375107E4,0x260AE804,0x374AE804,0x3006FBE4
,0xA806FBE4,0xB605FBE4,0x300CDC04,0x2686E804,0xA58EDC04,0x280D07E4
,0x300CDC04,0xB80DDC04,0x375107E4,0x261107E4,0xAE44F50C,0xB617DC04
,0x254AE804,0x255107E4,0x0843CC04,0x080CDC04,0x255107E4,0xA60AE804
,0xA61107E4,0xA74B279F,0x273EB7E4,0x080CDC04,0x261107E4,0x080CDC04
,0xB81107E4,0xAF5107E4,0x680D07E4,0x280D07E4,0x3806E804,0xA817DC04
,0x2605FBE4,0x8821CC04,0xAE1107E4,0x2B0D07E4,0x2443CC04,0xB00CDC04
,0x080D07E4,0x2F41CC04,0xA80DDC04,0xA74D07E4,0x080D07E4,0x273EB7E4
,0xA74D07E4,0xAD84FBE4,0x673CCC04,0x2807C009,0x255107E4,0x330CDC04
,0x884D07E4,0xA89107E4,0x255107E4,0x260AE804,0x280CDC04,0xA61107E4
			};

			std::ostringstream FirstTextByte;
			std::ostringstream FirstTextlength;

			for (char c : message)
			{
				FirstTextByte << std::bitset<8>(c);
			}
			int FirstTextByte_length = FirstTextByte.str().length();
			FirstTextByte << '1';
			FirstTextByte << '1';
			FirstTextByte << '0';
			while ((FirstTextByte.str().length() % 768) != 704)
			{
				FirstTextByte << '0';
			}
			FirstTextlength << std::bitset<64>(GodKey + FirstTextByte_length);
			FirstTextByte << FirstTextlength.str();

			//----------------------------------------

			int TempBytelength = FirstTextByte.str().length() / 768;
			std::vector<std::string> TempByteArray(TempBytelength);
			for (int i = 0, k = 0; i < FirstTextByte.str().length(); i += 768, k++)
			{
				TempByteArray[k] = FirstTextByte.str().substr(i, 768);
			}

			for (int x = 0; x < TempBytelength; x++)
			{
				uint32_t AngelArray[24];

				uint32_t splitByte[24];
				for (int i = 0, k = 0; i < TempByteArray[x].length(); i += 32, k++)
				{
					splitByte[k] = std::stoul(TempByteArray[x].substr(i, 32), nullptr, 2);
				}

				for (int i = 0; i <= 23; i++)
				{
					AngelArray[i] = (splitByte[i] + Angels[i % 24]);
				}

				for (int i = 0; i <= 23; i++)
				{
					AngelArray[(i + 2) % 24] = AngelArray[(i + 2) % 24] + ((AngelArray[i]) + (AngelArray[(i + 1) % 24]));
					Angels[(i + 23) % 24] = AngelArray[(i + 2) % 24];
				}
			}

			for (int i = 0; i < 38; i++)
			{
				uint32_t temp1 = e1 + (Angels[i % 24] ^ key[i]) + ((e5 << 9) | (e5 >> 23));
				uint32_t temp2 = e6 + (Angels[(i + 8) % 24] ^ key[i + 38]) + ((e2 << 8) | (e2 >> 24));
				uint32_t temp3 = e9 + (Angels[(i + 16) % 24] ^ key[i + 76]) + ((e8 << 7) | (e8 >> 25));

				e1 = e2; e2 = e3; e3 = e4; e4 = e5 + temp1;
				e5 = e6; e6 = e7; e7 = e8; e8 = e9 + temp2;
				e9 = e10; e10 = e11; e11 = e12; e12 = e1 + temp3;
			}

			std::ostringstream result;
			result << std::hex << (e1 + e2) << (e3 + e4) << (e5 + e6) << (e7 + e8) << (e9 + e10) << (e11 + e12);;

			return result.str();
		}
	};
	class SPB256
	{
	public:
		static const uint32_t GodKey = 0x300AE7F5;

		static std::string Hash(const std::string& message)
		{
			uint32_t e1 = 0x76662797;
			uint32_t e2 = 0xA2F0528E;
			uint32_t e3 = 0x2E9A9A9C;
			uint32_t e4 = 0x663085B9;
			uint32_t e5 = 0xED51D495;
			uint32_t e6 = 0x6F4DBBAC;
			uint32_t e7 = 0x7D43ADBE;
			uint32_t e8 = 0xB6A6A797;
			uint32_t e9 = 0xED51D495;
			uint32_t e10 = 0xB6A6A797;
			uint32_t e11 = 0x2630D28E;
			uint32_t e12 = 0xAF43ADC1;

			uint32_t Angels[24] = {
				0x40079CB5, 0x084DD54F, 0xB74D07D9, 0xAF4D84B7, 0x19218496, 0x2811AD87,
				0xAD4DD4A1, 0xA80D9D94, 0x3587D960, 0xB0078E69, 0xB00D84CC, 0x058F9031,
				0x280DA810, 0x058FA3C8, 0xAE9A7407, 0x2551AD8F, 0x374DBF7A, 0x258FA186,
				0x8741D3E3, 0xA312D4F0, 0xF8189A87, 0xB5DABDD3, 0x264FBDD3, 0x9BDABDD3
			};

			uint32_t key[114] = {
				0x374D07E4,0xA697DC04,0x26811752,0xA89107E4,0x255107E4,0x738EDC04
,0x680D07E4,0x738EDC04,0x380DDC04,0x088BE8EA,0xAD473E42,0x2911ACEA
,0x800D07E4,0x3F4D0755,0x380AE804,0xA61107E4,0x255107E4,0x3306FBE4
,0x2E90A0AC,0x259249E2,0x738EDC04,0x380AE804,0x260AE804,0xAB0DDC04
,0x374D07E4,0x2B0D07E4,0xAB0FFBE4,0x068D07E4,0xB00CDC04,0x380CDC04
,0x2551A643,0x0006E804,0x680D07E4,0x802B04FB,0xA75199AD,0x25904500
,0xAD5107E4,0x2D920DDD,0xA80FFBE4,0x3F4D8F00,0xB007BAD4,0x2617DC04
,0xB006E804,0x380AE804,0xA80D07E4,0x680D07E4,0xED51D495,0x3746E804
,0x380AE804,0x2D9245F6,0x281107E4,0xA58EDC04,0xA60AE804,0xB80FFBE4
,0x800D07E4,0x281107E4,0x375107E4,0x260AE804,0x374AE804,0x3006FBE4
,0xA806FBE4,0xB605FBE4,0x300CDC04,0x2686E804,0xA58EDC04,0x280D07E4
,0x300CDC04,0xB80DDC04,0x375107E4,0x261107E4,0xAE44F50C,0xB617DC04
,0x254AE804,0x255107E4,0x0843CC04,0x080CDC04,0x255107E4,0xA60AE804
,0xA61107E4,0xA74B279F,0x273EB7E4,0x080CDC04,0x261107E4,0x080CDC04
,0xB81107E4,0xAF5107E4,0x680D07E4,0x280D07E4,0x3806E804,0xA817DC04
,0x2605FBE4,0x8821CC04,0xAE1107E4,0x2B0D07E4,0x2443CC04,0xB00CDC04
,0x080D07E4,0x2F41CC04,0xA80DDC04,0xA74D07E4,0x080D07E4,0x273EB7E4
,0xA74D07E4,0xAD84FBE4,0x673CCC04,0x2807C009,0x255107E4,0x330CDC04
,0x884D07E4,0xA89107E4,0x255107E4,0x260AE804,0x280CDC04,0xA61107E4
			};

			std::ostringstream FirstTextByte;
			std::ostringstream FirstTextlength;

			for (char c : message)
			{
				FirstTextByte << std::bitset<8>(c);
			}
			int FirstTextByte_length = FirstTextByte.str().length();
			FirstTextByte << '1';
			FirstTextByte << '1';
			FirstTextByte << '0';
			while ((FirstTextByte.str().length() % 768) != 704)
			{
				FirstTextByte << '0';
			}
			FirstTextlength << std::bitset<64>(GodKey + FirstTextByte_length);
			FirstTextByte << FirstTextlength.str();

			//----------------------------------------

			int TempBytelength = FirstTextByte.str().length() / 768;
			std::vector<std::string> TempByteArray(TempBytelength);
			for (int i = 0, k = 0; i < FirstTextByte.str().length(); i += 768, k++)
			{
				TempByteArray[k] = FirstTextByte.str().substr(i, 768);
			}

			for (int x = 0; x < TempBytelength; x++)
			{
				uint32_t AngelArray[24];

				uint32_t splitByte[24];
				for (int i = 0, k = 0; i < TempByteArray[x].length(); i += 32, k++)
				{
					splitByte[k] = std::stoul(TempByteArray[x].substr(i, 32), nullptr, 2);
				}

				for (int i = 0; i <= 23; i++)
				{
					AngelArray[i] = (splitByte[i] + Angels[i % 24]);
				}

				for (int i = 0; i <= 23; i++)
				{
					AngelArray[(i + 2) % 24] = AngelArray[(i + 2) % 24] + ((AngelArray[i]) + (AngelArray[(i + 1) % 24]));
					Angels[(i + 23) % 24] = AngelArray[(i + 2) % 24];
				}
			}

			for (int i = 0; i < 38; i++)
			{
				uint32_t temp1 = e1 + (Angels[i % 24] ^ key[i]) + ((e5 << 9) | (e5 >> 23));
				uint32_t temp2 = e6 + (Angels[(i + 8) % 24] ^ key[i + 38]) + ((e2 << 8) | (e2 >> 24));
				uint32_t temp3 = e9 + (Angels[(i + 16) % 24] ^ key[i + 76]) + ((e8 << 7) | (e8 >> 25));

				e1 = e2; e2 = e3; e3 = e4; e4 = e5 + temp1;
				e5 = e6; e6 = e7; e7 = e8; e8 = e9 + temp2;
				e9 = e10; e10 = e11; e11 = e12; e12 = e1 + temp3;
			}

			std::ostringstream result;
			result << std::hex << (e1 + e12) << (e2 + e11) << (e3 + e10) << (e4 + e9) << (e5) << (e6) << (e7) << (e8);

			return result.str();
		}
	};
	class SPB288
	{
	public:
		static const uint32_t GodKey = 0x300AE7F5;

		static std::string Hash(const std::string& message)
		{
			uint32_t e1 = 0x76662797;
			uint32_t e2 = 0xA2F0528E;
			uint32_t e3 = 0x2E9A9A9C;
			uint32_t e4 = 0x663085B9;
			uint32_t e5 = 0xED51D495;
			uint32_t e6 = 0x6F4DBBAC;
			uint32_t e7 = 0x7D43ADBE;
			uint32_t e8 = 0xB6A6A797;
			uint32_t e9 = 0xED51D495;
			uint32_t e10 = 0xB6A6A797;
			uint32_t e11 = 0x2630D28E;
			uint32_t e12 = 0xAF43ADC1;

			uint32_t Angels[24] = {
				0x40079CB5, 0x084DD54F, 0xB74D07D9, 0xAF4D84B7, 0x19218496, 0x2811AD87,
				0xAD4DD4A1, 0xA80D9D94, 0x3587D960, 0xB0078E69, 0xB00D84CC, 0x058F9031,
				0x280DA810, 0x058FA3C8, 0xAE9A7407, 0x2551AD8F, 0x374DBF7A, 0x258FA186,
				0x8741D3E3, 0xA312D4F0, 0xF8189A87, 0xB5DABDD3, 0x264FBDD3, 0x9BDABDD3
			};

			uint32_t key[114] = {
				0x374D07E4,0xA697DC04,0x26811752,0xA89107E4,0x255107E4,0x738EDC04
,0x680D07E4,0x738EDC04,0x380DDC04,0x088BE8EA,0xAD473E42,0x2911ACEA
,0x800D07E4,0x3F4D0755,0x380AE804,0xA61107E4,0x255107E4,0x3306FBE4
,0x2E90A0AC,0x259249E2,0x738EDC04,0x380AE804,0x260AE804,0xAB0DDC04
,0x374D07E4,0x2B0D07E4,0xAB0FFBE4,0x068D07E4,0xB00CDC04,0x380CDC04
,0x2551A643,0x0006E804,0x680D07E4,0x802B04FB,0xA75199AD,0x25904500
,0xAD5107E4,0x2D920DDD,0xA80FFBE4,0x3F4D8F00,0xB007BAD4,0x2617DC04
,0xB006E804,0x380AE804,0xA80D07E4,0x680D07E4,0xED51D495,0x3746E804
,0x380AE804,0x2D9245F6,0x281107E4,0xA58EDC04,0xA60AE804,0xB80FFBE4
,0x800D07E4,0x281107E4,0x375107E4,0x260AE804,0x374AE804,0x3006FBE4
,0xA806FBE4,0xB605FBE4,0x300CDC04,0x2686E804,0xA58EDC04,0x280D07E4
,0x300CDC04,0xB80DDC04,0x375107E4,0x261107E4,0xAE44F50C,0xB617DC04
,0x254AE804,0x255107E4,0x0843CC04,0x080CDC04,0x255107E4,0xA60AE804
,0xA61107E4,0xA74B279F,0x273EB7E4,0x080CDC04,0x261107E4,0x080CDC04
,0xB81107E4,0xAF5107E4,0x680D07E4,0x280D07E4,0x3806E804,0xA817DC04
,0x2605FBE4,0x8821CC04,0xAE1107E4,0x2B0D07E4,0x2443CC04,0xB00CDC04
,0x080D07E4,0x2F41CC04,0xA80DDC04,0xA74D07E4,0x080D07E4,0x273EB7E4
,0xA74D07E4,0xAD84FBE4,0x673CCC04,0x2807C009,0x255107E4,0x330CDC04
,0x884D07E4,0xA89107E4,0x255107E4,0x260AE804,0x280CDC04,0xA61107E4
			};

			std::ostringstream FirstTextByte;
			std::ostringstream FirstTextlength;

			for (char c : message)
			{
				FirstTextByte << std::bitset<8>(c);
			}
			int FirstTextByte_length = FirstTextByte.str().length();
			FirstTextByte << '1';
			FirstTextByte << '1';
			FirstTextByte << '0';
			while ((FirstTextByte.str().length() % 768) != 704)
			{
				FirstTextByte << '0';
			}
			FirstTextlength << std::bitset<64>(GodKey + FirstTextByte_length);
			FirstTextByte << FirstTextlength.str();

			//----------------------------------------

			int TempBytelength = FirstTextByte.str().length() / 768;
			std::vector<std::string> TempByteArray(TempBytelength);
			for (int i = 0, k = 0; i < FirstTextByte.str().length(); i += 768, k++)
			{
				TempByteArray[k] = FirstTextByte.str().substr(i, 768);
			}

			for (int x = 0; x < TempBytelength; x++)
			{
				uint32_t AngelArray[24];

				uint32_t splitByte[24];
				for (int i = 0, k = 0; i < TempByteArray[x].length(); i += 32, k++)
				{
					splitByte[k] = std::stoul(TempByteArray[x].substr(i, 32), nullptr, 2);
				}

				for (int i = 0; i <= 23; i++)
				{
					AngelArray[i] = (splitByte[i] + Angels[i % 24]);
				}

				for (int i = 0; i <= 23; i++)
				{
					AngelArray[(i + 2) % 24] = AngelArray[(i + 2) % 24] + ((AngelArray[i]) + (AngelArray[(i + 1) % 24]));
					Angels[(i + 23) % 24] = AngelArray[(i + 2) % 24];
				}
			}

			for (int i = 0; i < 38; i++)
			{
				uint32_t temp1 = e1 + (Angels[i % 24] ^ key[i]) + ((e5 << 9) | (e5 >> 23));
				uint32_t temp2 = e6 + (Angels[(i + 8) % 24] ^ key[i + 38]) + ((e2 << 8) | (e2 >> 24));
				uint32_t temp3 = e9 + (Angels[(i + 16) % 24] ^ key[i + 76]) + ((e8 << 7) | (e8 >> 25));

				e1 = e2; e2 = e3; e3 = e4; e4 = e5 + temp1;
				e5 = e6; e6 = e7; e7 = e8; e8 = e9 + temp2;
				e9 = e10; e10 = e11; e11 = e12; e12 = e1 + temp3;
			}

			std::ostringstream result;
			result << std::hex << (e1) << (e2) << (e3) << (e4) << (e5 + e7) << (e10 + e8) << (e6 + e9) << (e9 + e11) << (e10 + e12);
			return result.str();
		}
	};

	class SPB384
	{
	public: 
		static uint64_t GodKey; 
		static std::string Hash(const std::string& message) {
			uint64_t e1 = 0xC9C47481EA967B9B;
			uint64_t e2 = 0x4BC4748350704D19;
			uint64_t e3 = 0xAAECB4835079F4F6;
			uint64_t e4 = 0xD9FE76A2CCAE78E2;
			uint64_t e5 = 0xA95731C78331353B;
			uint64_t e6 = 0xD1F739C6B8157E27;
			uint64_t e7 = 0xFA4B72F32180355A;
			uint64_t e8 = 0xA4B5206204967C69;
			uint64_t e9 = 0xA95780332B31353B;
			uint64_t e10 = 0xCEE2BD4CF4967C69;
			uint64_t e11 = 0x5523B142AA704A4B;
			uint64_t e12 = 0xF9E5F34C6F7CE278;

			std::vector<uint64_t> Angels = {
				0xCCB5CD01E2A374AB, 0xC118E3516E7B8CB8, 0xD8B2998FB82BD850, 0xD918E458E4E49C48,
				0x1249934C6F8D7AD7, 0xC61F36FAE00874FA, 0xBE1A934C6F8A8AE8, 0x0D1A934B294C8948,
				0x8E96DA7E59BA5D79, 0x78097482DF9F6891, 0xB7B9D481E9E1C951, 0x64B1CD04D060F841,
				0x0D1A948361AB6C08, 0x50BE9A1A13F2F941, 0x66CCF34A1AC6EC86, 0x18B9D482DF762A73,
				0x788A47633A198D91, 0x0D6400E7EB937E1C, 0x93E5F484C6BAF0FB, 0xD35D134A192DA458,
				0x1246E7634CFB3666, 0xFF649B8BA22EC93D, 0x6983F7A7A232D9D5, 0xF3148EB3A22EC193
			};

			std::vector<uint64_t> key = {
				0x494A4313C75417D1, 0xF627BBF7C15BC36D, 0x687F7430C19BAC98, 0x468C24F9CD53E761,
				0x6D18DB23C753E643, 0x92BDCAB5C35BD873, 0x62785B55C35BD873, 0x92835B95C35BD873,
				0x9404BCBBC15BC50C, 0x53485358B135F781, 0x9CC4734B91360127, 0x411C9358B135F40B,
				0x3C1CBBBE9D5BC4B9, 0xD915BE062DFFB498, 0xB9F07FC69D5BCEF7, 0x203CBB129D53E760,
				0x5BB59B55C35BC793, 0x81B829869D56E35B, 0x955D134C6D1EEC06, 0x2DC47482934B53D9,
				0x937DA883B75BD873, 0x5349F4829D5BCEF7, 0xFF4C70ED7353E671, 0xA83EFFC69D53E6AE,
				0x33527991C35417D0, 0x1B785B55C354162B, 0x37B9BB129D53E761, 0x4766E8569D540AD3,
				0x89DEE8D7C1540C52, 0x325565169D5BC389, 0x6D1F2A34A1050E73, 0xBBE597DFC15BC4D8,
				0xF5A91951C35BD860, 0x80C47483624128F1, 0x341A934A171A2B41, 0x2DC47358B16A3C79,
				0x7CB2FB95C354169B, 0x2DC47481FD635931, 0x0AD35FC69D5BC1DB, 0x361A934A882F7598,
				0xD4AB334A09A252B8, 0x1E08194FB75416FB, 0x16C74BF9BD5BC1DA, 0xB3FD7855735BCDA2,
				0x5A7F1557B75BCEB4, 0xF593F991C35BD860, 0xA8B9D34C6D31353B, 0x6A8FF7B69D5417D1,
				0xB9E6FB55C35BCEF7, 0x2DC4734B6FD09931, 0x5E74794FB75BCBE6, 0x993EFFC69D5415D9,
				0xE6C9E5169D53E761, 0x9AD35FC69D540AC0, 0x1B3F50ED735BC4B9, 0xC7B3D597B953DC8A,
				0x34039BABC75BCEF6, 0x819F20FFC753E643, 0xC8637FC69D5BCEF7, 0x512A8313C753E670,
				0x571C94829D541688, 0x086D6C17C15BCEA6, 0x85807731BD53E670, 0x82C046BFC15BC25C,
				0xA31E3731BD541929, 0x0D57394FB75BC24E, 0xB28886A69D53E670, 0x044CE5169D540AD3,
				0x24B3B933C15BCEF7, 0x287043BDC553E643, 0x92C4734B3555BE92, 0x0AECB4829D5BCEA6,
				0xDCAEB0ED7353E641, 0x32FD9BADC553E642, 0x6C73385573540985, 0x64B64ECDC35BC880,
				0x3EC7C0A57353E642, 0xEE7B910E9D53E761, 0xEC57F557B953E761, 0x90C47481EA82B469,
				0x1C394803B75BC200, 0x6483BF31BB5BC880, 0x0DB50AB9BD53E643, 0x64B69605BD5BC880,
				0x1BD8427BC75BC37A, 0x7F742BF9BD541926, 0x627BEFF3B75BD873, 0xF1864EB3B7540D37,
				0xB5F07FC69D5417D1, 0xD26B9BBE9D5BC37B, 0x00D713CE9D54162A, 0x4E661B129D53E912,
				0x16E1D8329D541678, 0x8F9157B69D541618, 0x746216FA9D5BC1F9, 0xA324136A9D540C52,
				0xB9F19FC69D540AD3, 0x6A64A263C15BC298, 0x3466CB59735BC1DB, 0x71740E67B7540C45,
				0xC8747F53B9540AD3, 0x1CFDE6BFC15BC200, 0xE2D15FC69D540C45, 0xB7D419F3C153E751,
				0xED661B129D540B77, 0xE1CAF34A1AC9AC09, 0x6C90991F7153E643, 0x8B32FBADC556E35B,
				0xC0B2A055C556E2F8, 0x71D15FC69D53E761, 0xFBB9FBBE9D53E643, 0x95E965E9C35BC793,
				0xBB24136A9D5417CE, 0xEC4953CE9D53E761
			};

			std::stringstream FirstTextByte;
			std::stringstream FirstTextlength;

			for (char c : message) {
				FirstTextByte << std::bitset<8>(c);
			}
			int FirstTextByte_length = FirstTextByte.str().length();
			FirstTextByte << "11";
			while ((FirstTextByte.str().length() % 1536) != 1408) {
				FirstTextByte << '0';
			}
			GodKey += static_cast<uint64_t>(FirstTextByte_length);
			FirstTextlength << std::bitset<128>(GodKey);
			FirstTextByte << FirstTextlength.str();

			int TempBytelength = FirstTextByte.str().length() / 1536;
			std::vector<std::string> TempByteArray(TempBytelength);
			for (int i = 0, k = 0; i < FirstTextByte.str().length(); i += 1536, ++k) {
				TempByteArray[k] = FirstTextByte.str().substr(i, 1536);
			}

			for (int x = 0; x < TempBytelength; ++x) {
				std::vector<uint64_t> AngelArray(24);

				std::vector<uint64_t> splitByte(TempByteArray[x].length() / 64);
				for (int i = 0, k = 0; i < TempByteArray[x].length(); i += 64, ++k) {
					splitByte[k] = std::bitset<64>(TempByteArray[x].substr(i, 64)).to_ullong();
				}

				for (int i = 0; i <= 23; ++i) {
					AngelArray[i] = (splitByte[i] + Angels[i % 24]);
				}

				for (int i = 0; i <= 23; ++i) {
					AngelArray[(i + 2) % 24] = AngelArray[(i + 2) % 24] + ((AngelArray[i]) + (AngelArray[(i + 1) % 24]));
					Angels[(i + 23) % 24] = AngelArray[(i + 2) % 24];
				}
			}

			for (int i = 0; i < 38; ++i) {
				uint64_t temp1 = e1 + (Angels[i % 24] ^ key[i]) + ((e5 << 9) | (e5 >> 23));
				uint64_t temp2 = e6 + (Angels[(i + 8) % 24] ^ key[i + 38]) + ((e2 << 8) | (e2 >> 24));
				uint64_t temp3 = e9 + (Angels[(i + 16) % 24] ^ key[i + 76]) + ((e8 << 7) | (e8 >> 25));

				e1 = e2; e2 = e3; e3 = e4; e4 = e5 + temp1;
				e5 = e6; e6 = e7; e7 = e8; e8 = e9 + temp2;
				e9 = e10; e10 = e11; e11 = e12; e12 = e1 + temp3;
			}

			std::stringstream result;
			result << std::hex << std::uppercase
				<< std::setw(8) << std::setfill('0') << (e12 + e6)
				<< std::setw(8) << std::setfill('0') << (e11 + e5)
				<< std::setw(8) << std::setfill('0') << (e10 + e4)
				<< std::setw(8) << std::setfill('0') << (e9 + e3)
				<< std::setw(8) << std::setfill('0') << (e8 + e2)
				<< std::setw(8) << std::setfill('0') << (e7 + e1);

			return result.str();
		}
	};
	uint64_t SPB384::GodKey = 0xB2A711ACF336A8E2;

	class SPB512
	{
	public:
		static uint64_t GodKey;
		static std::string Hash(const std::string& message) {
			uint64_t e1 = 0xC9C47481EA967B9B;
			uint64_t e2 = 0x4BC4748350704D19;
			uint64_t e3 = 0xAAECB4835079F4F6;
			uint64_t e4 = 0xD9FE76A2CCAE78E2;
			uint64_t e5 = 0xA95731C78331353B;
			uint64_t e6 = 0xD1F739C6B8157E27;
			uint64_t e7 = 0xFA4B72F32180355A;
			uint64_t e8 = 0xA4B5206204967C69;
			uint64_t e9 = 0xA95780332B31353B;
			uint64_t e10 = 0xCEE2BD4CF4967C69;
			uint64_t e11 = 0x5523B142AA704A4B;
			uint64_t e12 = 0xF9E5F34C6F7CE278;

			std::vector<uint64_t> Angels = {
				0xCCB5CD01E2A374AB, 0xC118E3516E7B8CB8, 0xD8B2998FB82BD850, 0xD918E458E4E49C48,
				0x1249934C6F8D7AD7, 0xC61F36FAE00874FA, 0xBE1A934C6F8A8AE8, 0x0D1A934B294C8948,
				0x8E96DA7E59BA5D79, 0x78097482DF9F6891, 0xB7B9D481E9E1C951, 0x64B1CD04D060F841,
				0x0D1A948361AB6C08, 0x50BE9A1A13F2F941, 0x66CCF34A1AC6EC86, 0x18B9D482DF762A73,
				0x788A47633A198D91, 0x0D6400E7EB937E1C, 0x93E5F484C6BAF0FB, 0xD35D134A192DA458,
				0x1246E7634CFB3666, 0xFF649B8BA22EC93D, 0x6983F7A7A232D9D5, 0xF3148EB3A22EC193
			};

			std::vector<uint64_t> key = {
				0x494A4313C75417D1, 0xF627BBF7C15BC36D, 0x687F7430C19BAC98, 0x468C24F9CD53E761,
				0x6D18DB23C753E643, 0x92BDCAB5C35BD873, 0x62785B55C35BD873, 0x92835B95C35BD873,
				0x9404BCBBC15BC50C, 0x53485358B135F781, 0x9CC4734B91360127, 0x411C9358B135F40B,
				0x3C1CBBBE9D5BC4B9, 0xD915BE062DFFB498, 0xB9F07FC69D5BCEF7, 0x203CBB129D53E760,
				0x5BB59B55C35BC793, 0x81B829869D56E35B, 0x955D134C6D1EEC06, 0x2DC47482934B53D9,
				0x937DA883B75BD873, 0x5349F4829D5BCEF7, 0xFF4C70ED7353E671, 0xA83EFFC69D53E6AE,
				0x33527991C35417D0, 0x1B785B55C354162B, 0x37B9BB129D53E761, 0x4766E8569D540AD3,
				0x89DEE8D7C1540C52, 0x325565169D5BC389, 0x6D1F2A34A1050E73, 0xBBE597DFC15BC4D8,
				0xF5A91951C35BD860, 0x80C47483624128F1, 0x341A934A171A2B41, 0x2DC47358B16A3C79,
				0x7CB2FB95C354169B, 0x2DC47481FD635931, 0x0AD35FC69D5BC1DB, 0x361A934A882F7598,
				0xD4AB334A09A252B8, 0x1E08194FB75416FB, 0x16C74BF9BD5BC1DA, 0xB3FD7855735BCDA2,
				0x5A7F1557B75BCEB4, 0xF593F991C35BD860, 0xA8B9D34C6D31353B, 0x6A8FF7B69D5417D1,
				0xB9E6FB55C35BCEF7, 0x2DC4734B6FD09931, 0x5E74794FB75BCBE6, 0x993EFFC69D5415D9,
				0xE6C9E5169D53E761, 0x9AD35FC69D540AC0, 0x1B3F50ED735BC4B9, 0xC7B3D597B953DC8A,
				0x34039BABC75BCEF6, 0x819F20FFC753E643, 0xC8637FC69D5BCEF7, 0x512A8313C753E670,
				0x571C94829D541688, 0x086D6C17C15BCEA6, 0x85807731BD53E670, 0x82C046BFC15BC25C,
				0xA31E3731BD541929, 0x0D57394FB75BC24E, 0xB28886A69D53E670, 0x044CE5169D540AD3,
				0x24B3B933C15BCEF7, 0x287043BDC553E643, 0x92C4734B3555BE92, 0x0AECB4829D5BCEA6,
				0xDCAEB0ED7353E641, 0x32FD9BADC553E642, 0x6C73385573540985, 0x64B64ECDC35BC880,
				0x3EC7C0A57353E642, 0xEE7B910E9D53E761, 0xEC57F557B953E761, 0x90C47481EA82B469,
				0x1C394803B75BC200, 0x6483BF31BB5BC880, 0x0DB50AB9BD53E643, 0x64B69605BD5BC880,
				0x1BD8427BC75BC37A, 0x7F742BF9BD541926, 0x627BEFF3B75BD873, 0xF1864EB3B7540D37,
				0xB5F07FC69D5417D1, 0xD26B9BBE9D5BC37B, 0x00D713CE9D54162A, 0x4E661B129D53E912,
				0x16E1D8329D541678, 0x8F9157B69D541618, 0x746216FA9D5BC1F9, 0xA324136A9D540C52,
				0xB9F19FC69D540AD3, 0x6A64A263C15BC298, 0x3466CB59735BC1DB, 0x71740E67B7540C45,
				0xC8747F53B9540AD3, 0x1CFDE6BFC15BC200, 0xE2D15FC69D540C45, 0xB7D419F3C153E751,
				0xED661B129D540B77, 0xE1CAF34A1AC9AC09, 0x6C90991F7153E643, 0x8B32FBADC556E35B,
				0xC0B2A055C556E2F8, 0x71D15FC69D53E761, 0xFBB9FBBE9D53E643, 0x95E965E9C35BC793,
				0xBB24136A9D5417CE, 0xEC4953CE9D53E761
			};

			std::stringstream FirstTextByte;
			std::stringstream FirstTextlength;

			for (char c : message) {
				FirstTextByte << std::bitset<8>(c);
			}
			int FirstTextByte_length = FirstTextByte.str().length();
			FirstTextByte << "11";
			while ((FirstTextByte.str().length() % 1536) != 1408) {
				FirstTextByte << '0';
			}
			GodKey += static_cast<uint64_t>(FirstTextByte_length);
			FirstTextlength << std::bitset<128>(GodKey);
			FirstTextByte << FirstTextlength.str();

			int TempBytelength = FirstTextByte.str().length() / 1536;
			std::vector<std::string> TempByteArray(TempBytelength);
			for (int i = 0, k = 0; i < FirstTextByte.str().length(); i += 1536, ++k) {
				TempByteArray[k] = FirstTextByte.str().substr(i, 1536);
			}

			for (int x = 0; x < TempBytelength; ++x) {
				std::vector<uint64_t> AngelArray(24);

				std::vector<uint64_t> splitByte(TempByteArray[x].length() / 64);
				for (int i = 0, k = 0; i < TempByteArray[x].length(); i += 64, ++k) {
					splitByte[k] = std::bitset<64>(TempByteArray[x].substr(i, 64)).to_ullong();
				}

				for (int i = 0; i <= 23; ++i) {
					AngelArray[i] = (splitByte[i] + Angels[i % 24]);
				}

				for (int i = 0; i <= 23; ++i) {
					AngelArray[(i + 2) % 24] = AngelArray[(i + 2) % 24] + ((AngelArray[i]) + (AngelArray[(i + 1) % 24]));
					Angels[(i + 23) % 24] = AngelArray[(i + 2) % 24];
				}
			}

			for (int i = 0; i < 38; ++i) {
				uint64_t temp1 = e1 + (Angels[i % 24] ^ key[i]) + ((e5 << 9) | (e5 >> 23));
				uint64_t temp2 = e6 + (Angels[(i + 8) % 24] ^ key[i + 38]) + ((e2 << 8) | (e2 >> 24));
				uint64_t temp3 = e9 + (Angels[(i + 16) % 24] ^ key[i + 76]) + ((e8 << 7) | (e8 >> 25));

				e1 = e2; e2 = e3; e3 = e4; e4 = e5 + temp1;
				e5 = e6; e6 = e7; e7 = e8; e8 = e9 + temp2;
				e9 = e10; e10 = e11; e11 = e12; e12 = e1 + temp3;
			}

			std::stringstream result;
			result << std::hex << std::uppercase
				<< std::setw(8) << std::setfill('0') << (e12 )
				<< std::setw(8) << std::setfill('0') << (e11 )
				<< std::setw(8) << std::setfill('0') << (e10 )
				<< std::setw(8) << std::setfill('0') << (e9 )
				<< std::setw(8) << std::setfill('0') << (e2 + e7)
				<< std::setw(8) << std::setfill('0') << (e3 + e8)
				<< std::setw(8) << std::setfill('0') << (e4 + e6)
				<< std::setw(8) << std::setfill('0') << (e5 + e1);

			return result.str();
		}
	};
	uint64_t SPB512::GodKey = 0xB2A711ACF336A8E2;

}

int main()
{
	bool runApp = true;
	while (runApp)
	{
		std::cout << "Please Enter Hash Mode Number" << std::endl;
		std::cout << "Number : 1 >>  128" << std::endl;
		std::cout << "Number : 2 >>  192" << std::endl;
		std::cout << "Number : 3 >>  256" << std::endl;
		std::cout << "Number : 4 >>  288" << std::endl;
		std::cout << "Number : 5 >>  384" << std::endl;
		std::cout << "Number : 6 >>  512" << std::endl;

		std::string HashMode;
		std::getline(std::cin, HashMode);

		std::cout << "Please Enter Word: ";
		std::string Words;
		std::getline(std::cin, Words);

		if (HashMode == "1")
		{
			std::cout << SPBHashing::SPB128::Hash(Words) << std::endl;
		}
		else if (HashMode == "2")
		{
			std::cout << SPBHashing::SPB192::Hash(Words) << std::endl;
		}
		else if (HashMode == "3")
		{
			std::cout << SPBHashing::SPB256::Hash(Words) << std::endl;
		}
		else if (HashMode == "4")
		{
			std::cout << SPBHashing::SPB288::Hash(Words) << std::endl;
		}
		else if (HashMode == "5")
		{
			std::cout << SPBHashing::SPB384::Hash(Words) << std::endl;
		}
		else if (HashMode == "6")
		{
			std::cout << SPBHashing::SPB512::Hash(Words) << std::endl;
		}
		else if (HashMode == "9")
		{
			runApp = false;
		}
		else
		{
			std::cout << "The input is invalid !!!" << std::endl;
			std::cout << "Please Try Again" << std::endl;
		}
	}
	return 0;
}
