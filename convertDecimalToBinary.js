// Program to convert decimal to binary number

const decimalNumber = 6;

let binaryNumber = 0;
let remainder = decimalNumber;
let digitOfBinaryNumber = 0;
let msbPositionValue = 1;

// console.log(decimalNumber, binaryNumber);

while (remainder > 0) {
    // console.log(digitOfBinaryNumber);
    // digitOfBinaryNumber = digitOfBinaryNumber - 1;
    digitOfBinaryNumber = remainder % 2;
    binaryNumber = (digitOfBinaryNumber * msbPositionValue) + binaryNumber;
    remainder = (remainder - (remainder % 2)) / 2;
    msbPositionValue = msbPositionValue * 10;
}

console.log(binaryNumber);