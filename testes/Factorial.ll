%struct.StringArray = type { i32, i8** }
declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@.fmt.int = private unnamed_addr constant [3 x i8] c"%d\00"
@.fmt.double = private unnamed_addr constant [6 x i8] c"%.16e\00"
@.fmt.str = private unnamed_addr constant [3 x i8] c"%s\00"
@.str.true = private unnamed_addr constant [5 x i8] c"true\00"
@.str.false = private unnamed_addr constant [6 x i8] c"false\00"

define i32 @factorial$i(i32 %p0) {
entry:
  %n.addr = alloca i32
  store i32 %p0, i32* %n.addr
  %t0 = load i32, i32* %n.addr
  %t1 = icmp eq i32 %t0, 0
  br i1 %t1, label %if.then0, label %if.else1
if.then0:
  ret i32 1
if.else1:
  br label %if.end2
if.end2:
  %t2 = load i32, i32* %n.addr
  %t3 = load i32, i32* %n.addr
  %t4 = sub i32 %t3, 1
  %t5 = call i32 @factorial$i(i32 %t4)
  %t6 = mul i32 %t2, %t5
  ret i32 %t6
}

define void @main$sa(%struct.StringArray %p0) {
entry:
  %args.addr = alloca %struct.StringArray
  store %struct.StringArray %p0, %struct.StringArray* %args.addr
  %argument = alloca i32
  store i32 0, i32* %argument
  %t0 = load %struct.StringArray, %struct.StringArray* %args.addr
  %t1 = extractvalue %struct.StringArray %t0, 1
  %t2 = getelementptr inbounds i8*, i8** %t1, i32 0
  %t3 = load i8*, i8** %t2
  %t4 = call i32 @atoi(i8* %t3)
  store i32 %t4, i32* %argument
  %t5 = load i32, i32* %argument
  %t6 = call i32 @factorial$i(i32 %t5)
  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.fmt.int, i32 0, i32 0), i32 %t6)
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
