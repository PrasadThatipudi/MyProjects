// Print the temparature of any city

#include <stdio.h>
#include <string.h>

void main()
{
	char CityName[100];

	printf("Enter city name: ");
	scanf("%s", CityName);

	char Var1[] = "curl \"https://api.openweathermap.org/data/2.5/weather?q=";
	char Var2[] = "&appid=abe3a0f4d0b6cebfbe7393b4b4e3aa28&units=metric\" > WeatherReport.txt";

	char ApiLink[200];

	sprintf(ApiLink, "%s%s%s", Var1, CityName, Var2);

	system(ApiLink);

	FILE *fpWeatherReport = fopen("WeatherReport.txt", "r");

	fseek(fpWeatherReport, 0, SEEK_END);

	int LengthOfWeatherData = ftell(fpWeatherReport);

	char WeatherData[LengthOfWeatherData];

	rewind(fpWeatherReport);

	fread(WeatherData, sizeof(WeatherData), 1, fpWeatherReport);

	fclose(fpWeatherReport);

	char* Temperature = strtok(WeatherData, ":");

	while (Temperature != NULL)
	{
		if (strcmp("{\"temp\"", token) == 0)
		{
			Temperature = strtok(NULL, ",");
			printf("\nCity name:%s\n", CityName);
			printf("Temperature: %s %cC\n", Temperature, 248);
			Temperature = NULL;
		}
		else
		{
			Temperature = strtok(NULL, ":");
		}
	}
}	
