# Python3 for Evaluating Arithmetic Expressions
valid_operators = ['+', '-', '*', '/']

# determine prrecedence of operators
def precedence(operator):
    if operator == '+' or operator == '-':
        return 1
    if operator == '*' or operator == '/':
        return 2
    return 0

# perform arithmetic operations
def apply_op(a, b, operator):
    if operator == '+': return a + b
    if operator == '-': return a - b 
    if operator == '*': return a * b 
    if operator == '/': return a / b

# main function
def evaluate(expression):

    # values and operators stack
    values = []
    ops = []

    i = 0
    # iterate through the string
    while i < len(expression):
        # skip whitespace
        if expression[i] == ' ':
            i += 1
            continue
        
        # if current char is opening bracket, push it to ops stack
        elif expression[i] == '(':
            ops.push(expression[i])

        # if current char is digit, push it to values stack
        elif expression[i].isdigit():
            values.push(expression[i])

        # if current char is closing bracket, resolve this brace
        elif expression[i] == ')':
            # if less than 2 elements in values stack, cannot perform operation to resolve this brace, so invalid
            if len(values) < 2 or ops.peek() == '(':
                return "NotWellFormed"

            # while ops stack is not empty and the top item is not opening bracket
            while len(ops) != 0 and ops.peek() != '(':
                # take note of ORDER here
                val_2 = values.pop()
                val_1 = values.pop()
                operator = ops.pop()
                # perform the operation
                result = apply_op(val_1, val_2, operator)
                # push result to value stack
                values.push(result)

            # pop the opening brace, this bracket is done
            if ops.peek() != '(':
                return "NotWellFormed"
            else:
                ops.pop()
    
        # if current char is any other valid operator
        elif expression[i] in valid_operators:
            # if ops stack is empty (no big brackets around whole expression), then invalid
            if len(ops) == 0:
                return "NotWellFormed"

            # while top of ops stack has the same or greater precedence than current operator
            # apply operator from top of ops stack to the top 2 elements of values stack
            while len(ops) != 0 and len(values) >= 2 and (precedence(ops.peek()) >= precedence(expression[i])):
                # take note of ORDER here
                val_2 = values.pop()
                val_1 = values.pop()
                operator = ops.pop()
                # perform the operation
                result = apply_op(val_1, val_2, operator)
                # push result to value stack
                values.push(result)

            # push current operator to ops stack
            ops.push(expression[i])

        # not a valid input (not whitespace / digit / valid operator)
        else:
            return "NotWellFormed"

        # increment i and read in next char in expression
        i += 1
    
    # at end of while-loop, no more inputs, but if only one of values/ops stack is non-empty then invalid
    if bool(ops) != bool(values):
        return "NotWellFormed"

    # Entire expression has been parsed at this point
    # second while-loop to apply remaining operators from ops stack
    # to remaining values from values stack
    while len(ops) != 0:
        # take note of ORDER here
        val_2 = values.pop()
        val_1 = values.pop()
        operator = ops.pop()
        # perform the operation
        result = apply_op(val_1, val_2, operator)
        # push result to value stack
        values.push(result)
    
    # Top item in values stack is the result
    return values.pop()
        





