#include "navigation.h"
#include <stdio.h>
#include "control.h"

uint8_t NavRecBuff[500];
uint8_t NavRecFifoBuff[500];
uint16_t NavRecLength;
uint16_t NavFifoLength;

#define PI 3.14159265358979323846
#define EARTH_RADIUS 6378137.0         // 地球长半轴 (WGS84)
#define EARTH_ECCEN 0.081819190842622 // 地球第一偏心率 (WGS84)

ENU_Coord enu;  // 定义全局ENU坐标变量
LLA_Coord p_lla,p0_lla;

FDILink_VersionData_Packet_t VersionData;
FDILink_IMUData_Packet_t IMUData;
FDILink_AHRSData_Packet_t AHRSData;
FDILink_INSGPSData_Packet_t INSGPSData;
System_State_Packet_t System_State_data;
Unix_Time_Packet_t TimeData;
Formatted_Time_Packet_t FTimeData;
Position_Standard_Deviation_Packet_t Position_Standard_Deviation_data;
Velocity_Standard_Deviation_Packet_t Velocity_Standard_Deviation_data;
Euler_Orientation_Standard_Deviation_Packet_t Euler_Orientation_Standard_Deviation_data;
Quaternion_Orientation_Standard_Deviation_Packet_t Quaternion_Orientation_Standard_Deviation_data;
Raw_Sensors_Packet_t Raw_Sensors_data;
Raw_GNSS_Packet_t Raw_GNSS_data;
Satellites_Packet_t Satellites_data;
Detailed_Satellites_Packet_t Detailed_Satellites_data;
Geodetic_Position_Packet_t Geodetic_Position_data;
ECEF_Position_Packet_t ECEF_Position_data;
UTM_Position_Packet_t UTM_Position_data;
NED_Velocity_Packet_t NED_Velocity_data;
Body_Velocity_Packet_t Body_Velocity_data;
Acceleration_Packet_t Acceleration_data;
Body_Acceleration_Packet_t Body_Acceleration_data;
Euler_Orientation_Packet_t Euler_Orientation_data;
Quaternion_Orientation_Packet_t Quaternion_Orientation_data;
DCM_Orientation_Packet_t DCM_Orientation_data;
Angular_Velocity_Packet_t Angular_Velocity_data;
Angular_Acceleration_Packet_t Angular_Acceleration_data;
External_Position_And_Velocity_Packet_t External_Position_And_Velocity_data;
External_Position_Packet_t External_Position_data;
External_Velocity_Packet_t External_Velocity_data;
External_Body_Velocity_Packet_t External_Body_Velocity_data;
External_Heading_Packet_t External_Heading_data;
External_Time_Packet_t External_Time_data;
External_Depth_Packet_t External_Depth_data;
External_Pitot_Pressure_Packet_t External_Pitot_Pressure_data;

FDILink_Status_t _FDILink;

QueueHandle_t NavQueue;
SemaphoreHandle_t NavSemaphore;//导航任务二值信号量
BaseType_t NavHigherTaskSwitch;

void NavigationSolution(void)
{
	fdiComProtocolReceive(&_FDILink, NavRecFifoBuff, NavRecLength);
}

// 将LLA坐标转换为ECEF坐标
ECEF_Coord lla_to_ecef(LLA_Coord lla) {
    double lat_rad = lla.lat;
    double lon_rad = lla.lon;
    double N = EARTH_RADIUS / sqrt(1.0 - EARTH_ECCEN * EARTH_ECCEN * sin(lat_rad) * sin(lat_rad));
    
    ECEF_Coord ecef;
    ecef.x = (N + lla.alt) * cos(lat_rad) * cos(lon_rad);
    ecef.y = (N + lla.alt) * cos(lat_rad) * sin(lon_rad);
    ecef.z = (N * (1.0 - EARTH_ECCEN * EARTH_ECCEN) + lla.alt) * sin(lat_rad);
    
    return ecef;
}

// 计算P相对于P0的ENU坐标
ENU_Coord ecef_to_enu(ECEF_Coord p, ECEF_Coord p0, LLA_Coord lla0) {
    // 将参考点LLA转换为弧度
    double lat_rad = lla0.lat;
    double lon_rad = lla0.lon;
    
    // 计算ECEF到ENU的旋转矩阵元素
    double sin_lat = sin(lat_rad);
    double cos_lat = cos(lat_rad);
    double sin_lon = sin(lon_rad);
    double cos_lon = cos(lon_rad);
    
    // 计算P相对于P0的ECEF坐标差
    double dx = p.x - p0.x;
    double dy = p.y - p0.y;
    double dz = p.z - p0.z;
    
    // 应用旋转矩阵得到ENU坐标
    ENU_Coord enu;
    enu.east  = -sin_lon * dx + cos_lon * dy;
    enu.north = -sin_lat * cos_lon * dx - sin_lat * sin_lon * dy + cos_lat * dz;
    enu.up    = cos_lat * cos_lon * dx + cos_lat * sin_lon * dy + sin_lat * dz;
    
    return enu;
}



void LocalCcoordinate(void)
{

    // 初始化参考点（仅在第一次或ControlTime为0时更新）
    if(ControlTime == 0){
        p0_lla.lon = Geodetic_Position_data.Longitude;
        p0_lla.lat = Geodetic_Position_data.Latitude;
        p0_lla.alt = Geodetic_Position_data.Height;
    }
    
    // 当前点经纬高
        p_lla.lon = Geodetic_Position_data.Longitude;
        p_lla.lat = Geodetic_Position_data.Latitude;
        p_lla.alt = Geodetic_Position_data.Height;
 
    
    // 转换为ECEF坐标
    ECEF_Coord p0_ecef = lla_to_ecef(p0_lla);
    ECEF_Coord p_ecef = lla_to_ecef(p_lla);
    
    // 计算ENU坐标（更新全局enu变量）
    enu = ecef_to_enu(p_ecef, p0_ecef, p0_lla);
}
