#ifndef MODBUS_H
#define MODBUS_H

typedef unsigned char byte;

template< typename T >  
void bcd2dec(byte * buf, int digits, T * value)
{
	T tmp = 0;
	byte mask_l = 0x0F,
		 mask_h = 0xF0;
	for (int i = 0; i < digits; i++)
	{
		byte digit = 0;
		if (i % 2 == 0)
		{
			digit = (buf[(int)(i * 0.5)] & mask_h) >> 4;
		}
		else
		{
			digit = (buf[(int)(i * 0.5)] & mask_l);
		}
		for (int j = 1; j < digits - i; j++) digit *= 10;
		tmp += digit;
	}
	memcpy(value, &tmp, sizeof(T));
}

template< typename T >  
T swapBytes(T value)
{
	T num = ~0;
	for (quint32 i = 0; i < sizeof(T); i++)
	{
		if (i < sizeof(T) * 0.5)
		{
			num &= ~(0x00 | (0xff << ((sizeof(T) - i - 1) * 8))) | ((value & (0xff << (i * 8))) << (int)(((sizeof(T) * 4)/(i + 1)) + (8 * (sizeof(T) * 0.5 - i - 1))));
		}
		else
		{
			num &= ~(0x00 | (0xff << ((sizeof(T) - i - 1) * 8))) | 
			        ((value & (0xff << (i * 8))) >> (int)(((sizeof(T) * 4)/(sizeof(T) - i)) + 
					(8 * (i - (sizeof(T) * 0.5)))));
		}
	}
	return num;
}

template< typename T >  
T swapBits(T value, byte group = 1)
{
	T num = 0;
	T mask = 0;
	
	for (int i = 0; i < group; i++)
	{
		mask |= 1 << i;
	}
	
	for (quint32 i = 0; i < sizeof(T) * 8; i += group)
	{
		if (i < sizeof(T) * 4)
		{
			num |= ((mask << i) & value) << (sizeof(T) * 8 - group - i * 2);
#ifdef __TRACE__
			printf("%d: mask: %d shl: %d result: %d temp: %d\n", 
				   i, 
				   mask << i, 
				   (sizeof(T) * 8 - group - i * 2), 
				   (1 << i) & value, 
				   ((1 << i) & value) << (sizeof(T) * 8 - group - i * 2));
#endif
		}
		else
		{
			num |= ((mask << i) & value) >> qAbs(group + i * 2 - sizeof(T) * 8);
#ifdef __TRACE__
			printf("%d: mask: %d shr: %d result: %d temp: %d\n", 
				   i, 
				   mask << i, 
				   qAbs(group + i * 2 - sizeof(T) * 8), 
				   (1 << i) & value, 
				   ((1 << i) & value) >> qAbs(group + i * 2 - sizeof(T) * 8));
#endif
		}
	}
	return num;
}

template <typename T>
T readPackage(unsigned char * buffer, T * result)
{
	*result = 0;
	for (quint16 i = 1; i <= sizeof(T); i++)
	{
		(*result) |= buffer[i - 1] << ((sizeof(T) - i) * 8);
		//printf("%X\n", *result);
	}
	return *result;
}

template <typename T>
T readPackage(unsigned char * buffer, T * result, T mask)
{
	*result = 0;
	for (quint16 i = 1; i <= sizeof(T); i++)
	{
		(*result) |= buffer[i - 1] << ((sizeof(T) - i) * 8);
		//printf("%X\n", *result);
	}
	*result &= mask;
	return *result;
}

template <typename T>
void writePackage(unsigned char * buffer, T value)
{
	for (qint16 i = sizeof(T) - 1; i >= 0 ; i--)
	{
		buffer[i] = value & 0xFF;
		//printf("%d - %.2X\n", i, value & 0xFF);
		if (i > 0) value = value >> 8;
		//printf("value - %X\n", value);
	}
}

template <typename T>
T min(T v1, T v2)
{
	if (v1 <= v2)
		return v1;
	else
		return v2;
}


#endif // MODBUS_H
