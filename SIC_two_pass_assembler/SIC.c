#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int pass1();

int pass2();

int main()
{
	pass1();
	pass2();
	return 0;
}

int pass1()
{
	char buffer[64], label[12], mnemonic[8], operand[12], mnem[8], op[2], symbol[12];
	int start = 0X0, locctr = 0X0, ret, flag = 0, address = 0X0, j, program_length = 0X0, count = 0X0;
	FILE *fInput, *fSymtab, *fOptab, *fIntrm, *fLen;

	fInput = fopen("input.txt", "r");
	if (fInput != NULL)
	{
		printf("%s\n", "input.txt file found.");
	}
	else
	{
		printf("%s\n", "Can not find input.txt file.");
		return 0;
	}

	fSymtab = fopen("SYMTAB.txt", "w+");

	fOptab = fopen("OPTAB.txt", "r");
	if (fOptab != NULL)
	{
		printf("%s\n", "OPTAB.txt file found.");
	}
	else
	{
		printf("%s\n", "Can not find OPTAB.txt file.");
		return 0;
	}

	fIntrm = fopen("intermediate.txt", "w");

	fgets(buffer, 64, fInput); // read first input line
	sscanf(buffer, "%s %s %s", label, mnemonic, operand);

	if (strcmp(mnemonic, "START") == 0)
	{																			 // mnemonic = START
		locctr = atoi(operand);													 // save operand as starting address
		locctr = start;															 // initialize locctr to starting address
		fprintf(fIntrm, "%X\t %s\t %s\t %s\n", start, label, mnemonic, operand); // write line to intermediate file
		while (locctr > 0)
		{ // read next input line
			start = start + (locctr % 10) * pow(16, count);
			locctr = locctr / 10;
			count++;
		}
	}
	else
	{
		locctr = 0X0; // initialize locctr to 0
	}
	while (!feof(fInput))
	{
		fgets(buffer, 64, fInput);
		ret = sscanf(buffer, "%s %s %s", label, mnemonic, operand);

		if (label[0] != '.')
		{ // not a comment line
			switch (ret)
			{
			case 1:
				strcpy(mnemonic, label);
				fprintf(fIntrm, "%04X\t\t %s\n", locctr, mnemonic);
				break;
			case 2:
				strcpy(operand, mnemonic);
				strcpy(mnemonic, label);
				fprintf(fIntrm, "%X\t\t %s\t %s\n", locctr, mnemonic, operand);
				break;
			case 3:
				rewind(fSymtab);
				while (!feof(fSymtab))
				{ // search symtab for label
					flag = 0;
					fscanf(fSymtab, "%s %X", symbol, &address);
					if (strcmp(label, symbol) == 0)
					{
						flag = 1; // duplicate symbol
						printf("\nDuplicate LABEL found: %s", label);
						return 0;
					}
				}

				if (flag == 0)
				{ // no duplicate symbol
					fprintf(fSymtab, "%s\t %X\n", label, locctr);
					fprintf(fIntrm, "%X\t %s\t %s\t %s\n", locctr, label, mnemonic, operand);
				}
				break;
			default:
				break;
			}

			rewind(fOptab);
			while (!feof(fOptab))
			{ // search optab for opcode
				fscanf(fOptab, "%s %s", mnem, &op);
				if (strcmp(mnemonic, mnem) == 0)
				{
					locctr += 3;
					flag = 0;
					break;
				}
				else if (strcmp(mnemonic, "WORD") == 0)
				{ // mnemonic = WORD
					locctr += 3;
					flag = 0;
					break;
				}
				else if (strcmp(mnemonic, "RESW") == 0)
				{ // mnemonic = RESW
					locctr += 3 * atoi(operand);
					flag = 0;
					break;
				}
				else if (strcmp(mnemonic, "RESB") == 0)
				{ // mnemonic = RESB
					locctr += atoi(operand);
					flag = 0;
					break;
				}
				else if (strcmp(mnemonic, "BYTE") == 0)
				{
					j = strlen(operand); // find length of constant in bytes
					if (operand[0] != 'C' && operand[0] != 'X')
					{
						locctr += 1;
						flag = 0;
						break;
					}
					else if (strcmp(mnemonic, "BYTE") == 0 && operand[0] == 'C')
					{
						locctr += j - 3;
						flag = 0;
						break;
					}
					else if (strcmp(mnemonic, "BYTE") == 0 && operand[0] == 'X')
					{
						if ((j - 3) % 2 != 0)
						{
							locctr += (j - 3) / 2 + 1;
						}
						else
						{
							locctr += (j - 3) / 2;
						}
						flag = 0;
						break;
					}
					else
					{
						flag = 1;
					}
				}
				if (flag == 1)
				{
					printf("\n%s can not find in OPTAB.", mnemonic);
					return 0;
				}
			}
		}
	}

	fLen = fopen("program_length.txt", "w");
	program_length = locctr - start;
	fprintf(fLen, "%X", program_length);

	fclose(fInput);
	fclose(fSymtab);
	fclose(fOptab);
	fclose(fIntrm);
	fclose(fLen);
	return 1;
}

int pass2()
{
	int locctr = 0X0, start = 0X0, sa = 0X0, program_length = 0X0, ret, op_status = 0, address = 0X0, target = 0X0, ascii = 0X0, temp1 = 0X0, j, k, count = 0X0, record_len = 0X0;
	char label[12], mnemonic[8], operand[12], buffer[64], mnem[8], op[2], symbol[12], opcode[2], cons[8];
	long int aseek, bseek;
	FILE *fIntrm, *fSymtab, *fOptab, *fLen, *fObj;

	fIntrm = fopen("intermediate.txt", "r");
	if (fIntrm != NULL)
	{
		printf("%s\n", "intermediate.txt file found.");
	}
	else
	{
		printf("%s\n", "Can not find intermediate.txt file.");
		return 0;
	}
	fSymtab = fopen("SYMTAB.txt", "r");
	if (fSymtab != NULL)
	{
		printf("%s\n", "SYMTAB.txt file found.");
	}
	else
	{
		printf("%s\n", "Can not find SYMTAB.txt file.");
		return 0;
	}
	fOptab = fopen("OPTAB.txt", "r");
	if (fOptab != NULL)
	{
		printf("%s\n", "OPTAB.txt file found.");
	}
	else
	{
		printf("%s\n", "Can not find OPTAB.txt file.");
		return 0;
	}
	fLen = fopen("program_length.txt", "r");
	if (fLen != NULL)
	{
		printf("%s\n", "program_length.txt file found.");
	}
	else
	{
		printf("%s\n", "Can not find program_length.txt file.");
		return 0;
	}
	fObj = fopen("output.txt", "w");

	fscanf(fIntrm, "%X %s %s %s", &locctr, label, mnemonic, operand);
	if (strcmp(mnemonic, "START") == 0)
	{
		start = (int)strtol(operand, NULL, 16);
		fscanf(fLen, "%X", &program_length);
		fprintf(fObj, "H^%6s^%06X^%06X", label, start, program_length);
		fprintf(fObj, "\nT^%06X^00^", start);
		bseek = ftell(fObj);
	}

	fgets(buffer, 64, fIntrm);
	while (!feof(fIntrm))
	{
		fgets(buffer, 64, fIntrm);
		ret = sscanf(buffer, "%X %s %s %s", &locctr, label, mnemonic, operand);
		switch (ret)
		{
		case 2: // in case of RSUB
			strcpy(mnemonic, label);
			break;
		case 3: // label not present
			strcpy(operand, mnemonic);
			strcpy(mnemonic, label);
			break;
		default:
			break;
		}

		if (count >= 0X3C || strcmp(mnemonic, "RESB") == 0 || strcmp(mnemonic, "RESW") == 0 || strcmp(mnemonic, "END") == 0)
		{ // 0X3C is hex equivalent of 60
			aseek = ftell(fObj);
			fseek(fObj, -(aseek - bseek) - 3L, 1);
			record_len = count / 0X2;
			fprintf(fObj, "%02X^", record_len);
			fseek(fObj, 0L, 2);
			if (strcmp(mnemonic, "END") == 0)
			{
				break;
			}
			sa = locctr;
			if (strcmp(mnemonic, "RESW") != 0)
			{
				fprintf(fObj, "\nT^%06X^00^", sa);
			}
			bseek = ftell(fObj);
			count = 0X0;
		}

		rewind(fOptab);
		op_status = 0;
		while (!feof(fOptab))
		{
			fscanf(fOptab, "%s %s", mnem, op);
			if (strcmp(mnemonic, mnem) == 0)
			{
				strcpy(opcode, op);
				op_status = 1;
				break;
			}
		}
		if (op_status == 1 && operand[j - 1] == 'X' && operand[j - 2] == ',')
		{
			j = strlen(operand);
			operand[j - 2] = '\0';
			rewind(fSymtab);
			fscanf(fSymtab, "%s %X", symbol, &address);
			while (!feof(fSymtab))
			{
				if (strcmp(operand, symbol) == 0)
				{
					target = address;
					target += 0X8000;
					break;
				}
			}
			fprintf(fObj, "%2s%04X^", opcode, target);
			count = count + 0X6;
			continue;
		}
		else if (op_status == 1 && strcmp(mnemonic, "RSUB") != 0)
		{
			rewind(fSymtab);
			while (!feof(fSymtab))
			{
				fscanf(fSymtab, "%s %X", symbol, &address);
				if (strcmp(operand, symbol) == 0)
				{
					target = address;
					break;
				}
			}
			// printf("\nopcode=%s\ttarget=%X\n", opcode, target);
			fprintf(fObj, "%2s%04X^", op, target);
			count = count + 0X6;
			continue;
		}
		else if (op_status == 1 && strcmp(mnemonic, "RSUB") == 0)
		{
			fprintf(fObj, "%s0000^", opcode);
			count = count + 0X6;
			continue;
		}
		else
		{ // In case mnemonic field is an assembly directive.
			if ((strcmp(mnemonic, "BYTE") == 0))
			{
				if (operand[0] == 'C')
				{
					for (k = 0; k < strlen(operand) - 3; k++)
					{
						temp1 = 0x0;
						temp1 = temp1 + (int)operand[k + 2];
						ascii = ascii * 0x100 + temp1;
					}
					fprintf(fObj, "%6X^", ascii);
					count = count + strlen(operand) - 0X3;
				}
				else
				{
					for (k = 0; k < strlen(operand) - 3; k++)
					{
						cons[k] = operand[k + 2];
					}
					cons[k] = '\0';
					fprintf(fObj, "%s^", cons);
					count = count + (strlen(cons) + 0X0);
				}
				continue;
			}
			else if (strcmp(mnemonic, "WORD") == 0)
			{
				temp1 = (int)strtol(operand, NULL, 10);
				fprintf(fObj, "%06X^", temp1);
				count = count + 0X6;
				continue;
			}
			else
			{ // in case of RESB or RESW
				continue;
			}
		}
	}
	fprintf(fObj, "\nE^%06X", start);
	printf("\n%s\n", "Object Program written successfully.");
	fclose(fIntrm);
	fclose(fSymtab);
	fclose(fOptab);
	fclose(fLen);
	fclose(fObj);
	return 1;
}