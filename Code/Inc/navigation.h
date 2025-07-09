#ifndef __NAVIGATION_H 
#define __NAVIGATION_H

#include "FDILink.h"
#include "string.h"
#include "main.h"
#include "fdilink_decode.h"
#include "FDI_config.h"
#include "cmsis_os.h"

#define NavDMARecLength 500

#define PI 3.14159265358979323846
#define EARTH_RADIUS 6378137.0         // 地球长半轴 (WGS84)
#define EARTH_ECCEN 0.081819190842622 // 地球第一偏心率 (WGS84)

typedef struct {
    double x; // ECEF X坐标 (米)
    double y; // ECEF Y坐标 (米)
    double z; // ECEF Z坐标 (米)
} ECEF_Coord;

typedef struct {
    double lon; // 经度 (度)
    double lat; // 纬度 (度)
    double alt; // 高度 (米)
} LLA_Coord;

typedef struct {
    double east;  // 东向距离 (米)
    double north; // 北向距离 (米)
    double up;    // 天向距离 (米)
} ENU_Coord;

extern ENU_Coord enu; 


extern uint8_t NavRecBuff[];
extern uint8_t NavRecFifoBuff[];
extern uint16_t NavRecLength;
extern uint16_t NavFifoLength;

extern FDILink_VersionData_Packet_t VersionData;
extern FDILink_IMUData_Packet_t IMUData;
extern FDILink_AHRSData_Packet_t AHRSData;
extern FDILink_INSGPSData_Packet_t INSGPSData;
extern System_State_Packet_t System_State_data;
extern Unix_Time_Packet_t TimeData;
extern Formatted_Time_Packet_t FTimeData;
extern Position_Standard_Deviation_Packet_t Position_Standard_Deviation_data;
extern Velocity_Standard_Deviation_Packet_t Velocity_Standard_Deviation_data;
extern Euler_Orientation_Standard_Deviation_Packet_t Euler_Orientation_Standard_Deviation_data;
extern Quaternion_Orientation_Standard_Deviation_Packet_t Quaternion_Orientation_Standard_Deviation_data;
extern Raw_Sensors_Packet_t Raw_Sensors_data;
extern Raw_GNSS_Packet_t Raw_GNSS_data;
extern Satellites_Packet_t Satellites_data;
extern Detailed_Satellites_Packet_t Detailed_Satellites_data;
extern Geodetic_Position_Packet_t Geodetic_Position_data;
extern ECEF_Position_Packet_t ECEF_Position_data;
extern UTM_Position_Packet_t UTM_Position_data;
extern NED_Velocity_Packet_t NED_Velocity_data;
extern Body_Velocity_Packet_t Body_Velocity_data;
extern Acceleration_Packet_t Acceleration_data;
extern Body_Acceleration_Packet_t Body_Acceleration_data;
extern Euler_Orientation_Packet_t Euler_Orientation_data;
extern Quaternion_Orientation_Packet_t Quaternion_Orientation_data;
extern DCM_Orientation_Packet_t DCM_Orientation_data;
extern Angular_Velocity_Packet_t Angular_Velocity_data;
extern Angular_Acceleration_Packet_t Angular_Acceleration_data;
extern External_Position_And_Velocity_Packet_t External_Position_And_Velocity_data;
extern External_Position_Packet_t External_Position_data;
extern External_Velocity_Packet_t External_Velocity_data;
extern External_Body_Velocity_Packet_t External_Body_Velocity_data;
extern External_Heading_Packet_t External_Heading_data;
extern External_Time_Packet_t External_Time_data;
extern External_Depth_Packet_t External_Depth_data;
extern External_Pitot_Pressure_Packet_t External_Pitot_Pressure_data;

extern FDILink_Status_t _FDILink;

extern QueueHandle_t NavQueue;
extern SemaphoreHandle_t NavSemaphore;//导航任务二值信号量
extern BaseType_t NavHigherTaskSwitch;

void NavigationSolution(void);

ECEF_Coord lla_to_ecef(LLA_Coord lla);
ENU_Coord ecef_to_enu(ECEF_Coord p, ECEF_Coord p0, LLA_Coord lla0);

void LocalCcoordinate(void);
	
#endif
