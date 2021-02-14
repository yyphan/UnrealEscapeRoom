# UnrealEscapeRoom
An Unreal Escape Room from scratch

One small step for mankind, one giant leap for me.

# Things I Have Learnt Along the Way 
(Those I remembered to note down anyway)
1. You can create a pointer anytime you like. But you must check for null pointer before you try to access it. If not project will crash without logging any useful error messages.

```
AActor* HitActor = Hit.GetActor()
if(HitActor)
{
FString HitName = HitActor->GetName()
}
```
