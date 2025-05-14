# :hammer_and_wrench: Contributing to This Project

Thank you for contributing! I welcome contributions from everyone. However, to ensure a smooth experience, please follow the stebs below before you start coding!

--

## :clipboard: Contribution Process

**1. Create an Issue**
- Open a new GitHub Issue to propose a feature or report a bug.
- Provide a **Problem Statement**, **Proposed Solution**, **Acceptance Criteria**
- (Optional) Provide additional information, like anticipated **Difficulty** or anything else you might want to add.

**2. Create a Feature Branch**
- Branch off of `main` using a name in the format: 'feature' or 'bugfix'/two letter code to fuzzy identify yourself (doesn't have to be your real name)/issue number/30 character max description.
- Example: `feature/ds/1/contributions-style-guide`, `bugfix/lf/21/fixing-car-accel-bug` are two acceptable branch names, the first by me (Dakota Schaeffer) and the second by somebody who wishes to remain anonymous going by 'lordfarquad'.

**3. Link the Branch to the Issue**
- All branches must be linked to an issue to be accepted in a pull request.
- Add the branch in the GitHub Issue under the Development section.

**4. Make Pull Request**
- Push your branch and open a PR to `main`.
- Reference the issue again using `Fixes #<issue-number>` or `Closes #<issue-number>`.
- Make sure you mark elements of the **Acceptance Criteria** that are completed. If some or all elements are not completed, tell us why and why you think the PR should go ahead anyway.
- Make sure that your code follows our coding style.

**Issue Example**  
\# :art: Feature Request: Read From Standard In Buffer
Problem Statement  
\-\-  
The user application does not read the users input. There should be a system in place that can take keystrokes and use them to manipulate the line buffer of the file. Not only could this be used for line changes, but also to read interactive commands: like arrow-key up loads the previous command into standard in, etcetera.  

Proposed Solution  
\-\-  
Using `read()` from `unistd.h`, check the last character. If its an interactive character, then do a special command and display changes to stdout. If its not, then add it as a plain character to a separate string buffer and display changes to stdout. I am anticipating that changing stdout from the first message, so a `display_history` function is needed to change what is displayed in the input area.

Acceptance Criteria  
\-\-  
\- [ ] Create `input` header and c files.
\- [ ] Add one `uint8_t*` (string) buffer called `string_buffer`.
\- [ ] Add one `uint8_t` (char) buffer called `char_buffer`.
\- [ ] Create void function `void handle_read(uint16_t fd)`.

**Priority:** Medium
**Difficulty:** High

--

## :checkered_flag: Milestones
There will be a small few adding milestones, but there are opportunities to influence the creation of one via feature requests. However, because the project is tracking big feature development with milestones, there should be a style guide for how they look.

**1. Pick a Very Short and Descriptive Name for the Title**
- The title should convey what is being added in the fewest words possible.

**2. Describe What Will be Changed When Milestone is Complete**
- The description should focus on what will be different about the application after the milestone is complete.

**Milestone Title and Description Example**
User Interaction  

At the end of this milestone, a user will have an interface allowing them to make edits to a buffer. There will be commands that moves the user from line to line, change a line, add a line after the current line, before the current line, etc.
