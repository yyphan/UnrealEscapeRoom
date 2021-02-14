# UnrealEscapeRoom
An Unreal Escape Room from scratch

# Things I Have Learnt Along the Way 
(Those I remembered to note down anyway)
1. You can create a pointer (AActor* HitActor = Hit.GetActor()) anytime you like. But you must check for null pointer (if(HitActor)) before you try to access (FString HitName = HitActor->GetName()) it. If not project will crash without logging any useful error messages.
