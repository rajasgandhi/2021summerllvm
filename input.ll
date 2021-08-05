; ModuleID = 'input.c'
source_filename = "input.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [12 x i8] c"Hello World\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @function1() #0 {
  ret i32 1
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @function2() #0 {
  ret i32 2
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @function3() #0 {
  ret i32 3
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @function7() #0 {
  ret i32 5
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @function4() #0 {
  %1 = call i32 @function7()
  ret i32 %1
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @function5() #0 {
  ret i32 4
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @function6() #0 {
  %1 = call i32 @function5()
  %2 = add nsw i32 %1, 2
  ret i32 %2
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @function8() #0 {
  %1 = call i32 @function3()
  %2 = call i32 @function6()
  %3 = add nsw i32 %1, %2
  ret i32 %3
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str, i64 0, i64 0))
  %3 = call i32 @function1()
  %4 = sext i32 %3 to i64
  %5 = inttoptr i64 %4 to i8*
  %6 = call i32 (i8*, ...) @printf(i8* %5)
  %7 = call i32 @function2()
  %8 = sext i32 %7 to i64
  %9 = inttoptr i64 %8 to i8*
  %10 = call i32 (i8*, ...) @printf(i8* %9)
  %11 = call i32 @function3()
  %12 = sext i32 %11 to i64
  %13 = inttoptr i64 %12 to i8*
  %14 = call i32 (i8*, ...) @printf(i8* %13)
  %15 = call i32 @function4()
  %16 = sext i32 %15 to i64
  %17 = inttoptr i64 %16 to i8*
  %18 = call i32 (i8*, ...) @printf(i8* %17)
  %19 = call i32 @function5()
  %20 = sext i32 %19 to i64
  %21 = inttoptr i64 %20 to i8*
  %22 = call i32 (i8*, ...) @printf(i8* %21)
  %23 = call i32 @function6()
  %24 = sext i32 %23 to i64
  %25 = inttoptr i64 %24 to i8*
  %26 = call i32 (i8*, ...) @printf(i8* %25)
  %27 = call i32 @function8()
  %28 = sext i32 %27 to i64
  %29 = inttoptr i64 %28 to i8*
  %30 = call i32 (i8*, ...) @printf(i8* %29)
  ret i32 0
}

declare dso_local i32 @printf(i8*, ...) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0-4ubuntu1 "}
