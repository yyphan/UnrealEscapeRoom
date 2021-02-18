# UnrealEscapeRoom
An Unreal Escape Room from scratch

One small step for mankind, one giant leap for me.

Tech Demo(Not worth it): https://youtu.be/0eEZqHiYEBc

# Things I Have Learnt in Doing Demo 
(Those I remembered to note down anyway)
1. You can create a pointer anytime you like. But you must check for null pointer before you try to access it. If not project will crash without logging any useful error messages.

```
// header file
AActor* HitActor = nulllptr;
```
```
// implementation
AActor* HitActor = Hit.GetActor()
if(HitActor)
{
FString HitName = HitActor->GetName()
}
```
2. Everything derived from UObject, e.g. a ```UPhysicsHandleComponent```, should be created dynamically when the game starts, and that requires using a pointer. If not, we are creating game objects before the game world even exists.
3. In our header file(.h) ```#include``` section, remember to keep the “generated” header file at the bottom of all the includes. Because ```#include``` basically copy and paste the codes and for that reason all other header files should go above our generated header file. 
In our implementation file(.cpp) however, we should keep its header file at the TOP of the includes.
4. Turn on Eye Saver Mode
5. Pointer also can be useful when checking for existence. ```if(FHitResult)``` is not valid but it is good to go with ```AActor* ActorHit = FHitResult.GetActor(); if(ActorHit)```

