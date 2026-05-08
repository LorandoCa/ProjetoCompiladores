%struct.StringArray = type { i32, i8** }
declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt.int = private unnamed_addr constant [3 x i8] c"%d\00"
@.fmt.double = private unnamed_addr constant [6 x i8] c"%.16e\00"
@.fmt.str = private unnamed_addr constant [3 x i8] c"%s\00"
@.str.true = private unnamed_addr constant [5 x i8] c"true\00"
@.str.false = private unnamed_addr constant [6 x i8] c"false\00"
@.str.0 = private unnamed_addr constant [2 x i8] c"\0A\00"

@global_var = global i32 0

define void @main$sa(%struct.StringArray %p0) {
entry:
  %args.addr = alloca %struct.StringArray
  store %struct.StringArray %p0, %struct.StringArray* %args.addr
  %a = alloca i32
  store i32 0, i32* %a
  %b = alloca i1
  store i1 0, i1* %b
  %c = alloca double
  store double 0.0000000000000000e+00, double* %c
  store i32 1, i32* %a
  %t0 = load i32, i32* %a
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.int, i32 0, i32 0), i32 %t0)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  store i32 1, i32* %a
  %t1 = load i32, i32* %a
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.int, i32 0, i32 0), i32 %t1)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  %t2 = sub i32 0, 1
  store i32 %t2, i32* %a
  %t3 = load i32, i32* %a
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.int, i32 0, i32 0), i32 %t3)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  store i1 1, i1* %b
  %t4 = load i1, i1* %b
  %t5 = select i1 %t4, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.true, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.false, i32 0, i32 0)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* %t5)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  store i1 0, i1* %b
  %t6 = load i1, i1* %b
  %t7 = select i1 %t6, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.true, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.false, i32 0, i32 0)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* %t7)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  store double 2.0000000000000000e+00, double* %c
  %t8 = load double, double* %c
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt.double, i32 0, i32 0), double %t8)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  store double 2.2000000000000002e+00, double* %c
  %t9 = load double, double* %c
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt.double, i32 0, i32 0), double %t9)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  %t10 = sitofp i32 2 to double
  store double %t10, double* %c
  %t11 = load double, double* %c
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt.double, i32 0, i32 0), double %t11)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  store i32 1, i32* %a
  %t12 = load i32, i32* %a
  %t13 = sitofp i32 %t12 to double
  store double %t13, double* %c
  %t14 = load double, double* %c
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt.double, i32 0, i32 0), double %t14)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  store double 2.2000000000000002e+00, double* %c
  %t15 = load double, double* %c
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt.double, i32 0, i32 0), double %t15)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  %t16 = fsub double -0.0000000000000000e+00, 2.2000000000000002e+00
  store double %t16, double* %c
  %t17 = load double, double* %c
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt.double, i32 0, i32 0), double %t17)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  %t18 = load i32, i32* %a
  %t19 = sitofp i32 %t18 to double
  store double %t19, double* %c
  %t20 = load double, double* %c
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt.double, i32 0, i32 0), double %t20)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  %t21 = load i32, i32* %a
  %t22 = sub i32 0, %t21
  %t23 = sitofp i32 %t22 to double
  store double %t23, double* %c
  %t24 = load double, double* %c
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.fmt.double, i32 0, i32 0), double %t24)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  store i32 10, i32* @global_var
  %t25 = load i32, i32* @global_var
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.int, i32 0, i32 0), i32 %t25)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.str, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.0, i32 0, i32 0))
  ret void
}

define i32 @main(i32 %argc, i8** %argv) {
entry:
  %arg.count = sub i32 %argc, 1
  %arg.ptr = getelementptr inbounds i8*, i8** %argv, i32 1
  %args.0 = insertvalue %struct.StringArray zeroinitializer, i32 %arg.count, 0
  %args.1 = insertvalue %struct.StringArray %args.0, i8** %arg.ptr, 1
  call void @main$sa(%struct.StringArray %args.1)
  ret i32 0
}
