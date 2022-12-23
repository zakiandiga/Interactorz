#pragma once

#include "DrawDebugHelpers.h"

#define Debug_Log(Type, Message) UE_LOG(LogTemp, Type, Message);
#define SCREEN_LOG(Message, Color) if(GEngine) GEngine->AddOnScreenDebugMessage(1, 5, Color, Message);
#define DRAW_SPHERE(Location, Color) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, Color, true);
#define DRAW_LINE(Start, End, Color) if(GetWorld()) DrawDebugLine(GetWorld(), Start, End, Color, true, -1.f, 0, 1.f);
#define DRAW_POINT(Location, Color) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 20.f, Color, true);
#define DRAW_OBJECT(Location, TargetLook, Color) if(GetWorld()) \
		{\
			DrawDebugSphere(GetWorld(), Location, 25.f, 12, Color, true); \
			DrawDebugLine(GetWorld(), Location, TargetLook, Color, true, -1.f, 0, 1.f); \
			DrawDebugPoint(GetWorld(), TargetLook, 20.f, Color, true); \
		}
#define DRAW_SPHERE_Tick(Location, Color) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, Color, false, -1.f);
#define DRAW_LINE_Tick(Start, End, Color) if(GetWorld()) DrawDebugLine(GetWorld(), Start, End, Color, false, -1.f, 0, 1.f);
#define DRAW_POINT_Tick(Location, Color) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 20.f, Color, false, -1.f);
#define DRAW_OBJECT_Tick(Location, TargetLook, Color) if(GetWorld()) \
		{\
			DrawDebugSphere(GetWorld(), Location, 25.f, 12, Color, false, -1.f); \
			DrawDebugLine(GetWorld(), Location, TargetLook, Color, false, -1.f, 0, 1.f); \
			DrawDebugPoint(GetWorld(), TargetLook, 20.f, Color, false, -1.f); \
		}